/*
 * RowTable.cpp
 *
 *  Created on: Dec 10, 2014
 *      Author: volt
 */

#include "RowTable.h"
#include "../trans/TaskContext.h"
namespace expdb {

RowTable::RowTable() :
		m_priIndex(), m_desc(NULL), m_alloc() {
	// TODO Auto-generated constructor stub
	m_priIndex.init(0xffff);
}

RowTable::~RowTable() {
	// TODO Auto-generated destructor stub
}

/**
 * we dont check the description of row here
 */
int32_t RowTable::insert(RowKey key, const Row& row) {

	int32_t ret = SUCCESS;
	RowValue *ptr;
//	row.seriliaze(ptr);
	if ((ptr = (RowValue *) m_alloc.alloc(sizeof(QLock) + m_desc->getRowLen()))
			!= NULL) {
		if (SUCCESS == (set(ptr, row))) {
			ret = insert(key, ptr);
		}
	} else {
		ret = ERROR;
	}
	return ret;
}

int32_t RowTable::insert(RowKey key, RowValue* ptr) {

	int ret = SUCCESS;
	if (DUPKEY == (ret = m_priIndex.insert(key, ptr))) {

		VOLT_INFO("insert failed with dup key found");

		m_alloc.free(ptr);
	} else if (ERROR == ret) {
		VOLT_INFO("hash table is not properly initied");

		m_alloc.free(ptr);
	}
	return ret;
}

//refactor
int32_t RowTable::insert(TaskContext &ctx, const Row *row) {

	int32_t ret = SUCCESS;

	RowKey key;
	RowValue *value;

	LockInfo *lock = NULL;
	Logger *logger = NULL;
	if (SUCCESS != (ret = row->getRowKey(key))) {
		VOLT_WARN("Primary key is not provided");
		ret = INPUT_ERROR;
	} else if (SUCCESS != (ret = m_priIndex.find(key, value))) {

		if (NOTFOUND == ret) {
			if ( NULL
					== (value = (RowValue *) m_alloc.alloc(
							sizeof(QLock) + sizeof(int8_t)
									+ m_desc->getRowLen()))) {
				VOLT_WARN("Memory is not enough");
				ret = MEMORY_ERROR;
			} else {
				value->clear();
				value->setDeleted();
				if (SUCCESS != (ret = m_priIndex.insert(key, value))) {
					VOLT_WARN("Insert failure");
					ret = INDEX_ERROR;
				}
			}
		}
	}

	if (SUCCESS == ret) {

		if (SUCCESS != (ret = ctx.getLockInfo(lock))) {
			VOLT_ERROR("Context does not has lock info");
			ret = ERROR;
		} else if (SUCCESS != (ret = lock->writeBegin(value))) {
			VOLT_WARN("lock failure, value location: 0x%p, lock state: %d, owner: %d", value, value->m_lock.getValue(), value->m_lock.getOwner());
			ret = LOCK_CONFLICT;
			//post process here;
			//not here, the caller handle the lock failure
		} else if (!value->isDelete()) {

			ret = DUPKEY;
			VOLT_ERROR("Insert failure, primary key already exists");
		} else if (SUCCESS != (ret = ctx.getLogger(logger))) {
			VOLT_ERROR("Context does not has undo logger");
		} else if (SUCCESS != (ret = logger->undo(m_desc, value))) {
			VOLT_ERROR("Logger undo failed");
		} else if (SUCCESS != (ret = set(value, row))) {
			VOLT_WARN("modify row failure");
		}
	}

	if( SUCCESS != ret ) {
		ctx.setErrorCode(ret);
	}
	return ret;
}

//int32_t RowTable::insert(TaskContext& ctx, const Row *row) {
//
//	int32_t ret = SUCCESS;
//	RowKey key;
//	RowValue* value = NULL;
//	LockInfo *lock = NULL;	//todo
//
//	if (SUCCESS != ctx.getLockInfo(lock)) {
//
//		VOLT_ERROR("get lock failed");
//		ret = ERROR;
//	} else {
//
//		if (SUCCESS != (ret = row->getRowKey(key))) {
//
//			VOLT_DEBUG("get row key failed");
//		} else if (m_priIndex.find(key, value) == SUCCESS
//				&& !value->isDelete()) {
//
//			VOLT_TRACE("find a delete version in the index tree");
//		} else if (NULL
//				== (value = (RowValue *) m_alloc.alloc(
//						sizeof(QLock) + m_desc->getRowLen()))) {//bug here, alloc method get incorrect memory for the rowvalue
//
//			VOLT_DEBUG(("alloc memory for row failed"));
//		}
//
//		if (SUCCESS != (set(value, row))) {
//
//			VOLT_DEBUG("create row value failed");
//		} else if (SUCCESS != (ret = lock->writeBegin(value))) {//hold the lock of the value, avoid modify by other trans
//
//			VOLT_DEBUG("acquire lock failed");
//		} else if (SUCCESS != (ret = m_priIndex.insert(key, value))) {
//
//			if (DUPKEY == ret) {
//				VOLT_INFO("insert into index failed, dup key");
//			} else {
//				VOLT_DEBUG("insert into index failed, unknow");
//			}
//		}
//	}
//	return ret;
//}

int32_t RowTable::update(RowKey key, const Row& ptr) {

	int32_t ret = 0;

	RowValue *value;
	m_priIndex.find(key, value);

	set(value, ptr);

	return ret;
}

int32_t RowTable::update(TaskContext& ctx, RowKey key, Expression *expr) {

	int32_t ret = SUCCESS;
	LockInfo *lockinfo = NULL;
	Logger *logger = NULL;
	RowValue *value = NULL;
	if (SUCCESS != ctx.getLockInfo(lockinfo)) {
		VOLT_ERROR("get lock info failed");
		ret = ERROR;
	} else if (SUCCESS != m_priIndex.find(key, value) || value->isDelete()) { //how to ensure the primary index tree won't be modified, tree should be locked.
		VOLT_WARN("row does not existed");
		ret = NOT_EXIST;
	} else if (SUCCESS != lockinfo->writeBegin(value)) {
		VOLT_WARN("lock failed");
		ret = LOCK_CONFLICT;;
	} else {

		if (SUCCESS != (ret = ctx.getLogger(logger))) {
			VOLT_ERROR("Context does not has undo logger");
		} else if (SUCCESS != (ret = logger->undo(m_desc, value))) {
			VOLT_ERROR("Logger undo failed");
		} else {
			Row oldRow(m_desc);
			const Row *newRow;
			int64_t pos = 0;
			if (SUCCESS
					== oldRow.deserilization(value->m_value,
							m_desc->getRowLen(), pos)) {
				expr->cal(&oldRow, newRow);
				set(value, newRow);
			}
		}
	}
	if( ret != SUCCESS ) {
		ctx.setErrorCode(ret);
	}
	return ret;
}

int RowTable::setDesc(const RowDesc *desc) {

	m_desc = desc;

	return SUCCESS;
}

int32_t RowTable::remove(RowKey key) {

	return 0;
}

/**
 * 获得行记录
 */
int32_t RowTable::get(const RowKey key, Row& ref) {

	int32_t ret = SUCCESS;
	RowValue *value = NULL;
	if (ERROR == (ret = m_priIndex.find(key, value))) {
		VOLT_ERROR("Primary Index error");
	} else if (NOTFOUND == ret || value->isDelete()) {
		VOLT_WARN("Row not found");
		ret = NOTFOUND;
//		key.dump();
	} else {
		int64_t pos = 0;
		ref.setDesc(m_desc);
		ref.deserilization(value->m_value, m_desc->getRowLen(), pos);
	}
	return ret;
}

/**
 * 这里其实应该判断一下 row的desc和table的desc是不是一致
 */
int32_t RowTable::set(RowValue* value, const Row& row) {

	int32_t ret = SUCCESS;
	int64_t pos = 0;
	ret = row.serilization(value->m_value, m_desc->getRowLen(), pos);
	value->m_flag = value->m_flag & (~1);
	assert(pos == m_desc->getRowLen());
	return ret;
}

int32_t RowTable::set(RowValue* value, const Row* row) {

	int32_t ret = SUCCESS;
	int64_t pos = 0;
	ret = row->serilization(value->m_value, m_desc->getRowLen(), pos);
	value->m_flag = value->m_flag & (~1);
	assert(pos == m_desc->getRowLen());
	return ret;
}

} /* namespace expdb */

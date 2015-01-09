/*
 * RowTable.h
 *
 *  Created on: Dec 10, 2014
 *      Author: volt
 */

#ifndef ROWTABLE_H_
#define ROWTABLE_H_

#include "../common.h"
#include "../common/index/HashIndex.h"
#include "../common/memory/Allocator.h"
#include "Row.h"
#include "RowDesc.h"
#include "../trans/QLock.h"
#include "../exec/Expression.h"
namespace expdb {

typedef RowObj RowKey;

struct RowValue {

	QLock m_lock;
	int8_t m_flag;
	char m_value[0];

	bool isDelete() const{

		return m_flag & 1 == 1;
	}

	void setDeleted() {

		m_flag = m_flag | 1;
	}

};


template class HashIndex<RowKey, RowValue *>;

class TaskContext;
class LockInfo;


class RowTable {
public:

	class TableIterator{

	};


	RowTable();
	virtual ~RowTable();

	int setDesc(const RowDesc *desc);
	int	getDesc(const RowDesc *&desc){
		desc = m_desc;
		return SUCCESS;
	}
	int32_t insert(RowKey key, const Row &row);
	int32_t insert(RowKey key, RowValue *ptr);	//try to make it thread safe
	int32_t update(RowKey key, const Row &ptr);
	int32_t insert(TaskContext &ctx, const Row *row);
	int32_t update(TaskContext &ctx, const RowKey key, Expression *expr);
	int32_t remove(RowKey key);

	int32_t get(const RowKey key, Row &ref);

private:

	int32_t set(RowValue* value, const Row &row);
	int32_t set(RowValue* value, const Row *row);

	HashIndex<RowKey, RowValue *> m_priIndex;	//hold the index information
	const RowDesc *m_desc;				//descripe the structure of the row
	Allocator m_alloc;		//hold the raw data
};

} /* namespace expdb */

#endif /* ROWTABLE_H_ */

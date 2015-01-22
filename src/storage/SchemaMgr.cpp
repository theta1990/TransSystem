/*
 * SchemaMgr.cpp
 *
 *  Created on: Dec 19, 2014
 *      Author: volt
 */

#include "SchemaMgr.h"
#include <string.h>
namespace expdb {

SchemaMgr* SchemaMgr::ins__ = NULL;

SchemaMgr* SchemaMgr::getInstance() {

	if ( NULL == ins__) {
		ins__ = new SchemaMgr();
	}
	return ins__;
}

SchemaMgr::SchemaMgr() :
		m_tableCnt(0), m_schemaGuard() {

}

SchemaMgr::~SchemaMgr() {
	// TODO Auto-generated destructor stub
}

int32_t SchemaMgr::getTableDesc(const char* name, const RowDesc*& desc) {

	int ret = SUCCESS;
	int id;
	ScopedLock scopeLock(m_schemaGuard);

	if (SUCCESS != (ret = getTableId(name, id))) {

		VOLT_INFO("Table %s does not exist", name);
	} else {

		desc = &m_tableList[id].m_desc;
	}
	return ret;
}

int32_t SchemaMgr::getTableDesc(const int32_t tableId, const RowDesc*& desc) {

	int ret = SUCCESS;
	ScopedLock scopeLock(m_schemaGuard);

	if (tableId >= MAXTABLENUM) {

		ret = ERROR;
		VOLT_ERROR("Table id out of range");
	} else {
		//这里的赋值已经不是初始化了，所以可以，但我在gramma test中的例子是初始化赋值
		desc = &m_tableList[tableId].m_desc;
	}
	return ret;
}

int32_t SchemaMgr::addTable(const char* name, const RowDesc* desc, const RowDesc *&storedDesc) {

	int32_t ret = SUCCESS;
	int32_t id;
	ScopedLock scopeLock(m_schemaGuard);
	if (m_tableCnt >= MAXTABLENUM) {

		VOLT_INFO("Reach the max table count");
		ret = ERROR;
	} else if (SUCCESS == getTableId(name, id)) {

		VOLT_INFO("Detect duplicate table name");
		ret = ERROR;
	} else {

		m_tableList[m_tableCnt].m_tableId = m_tableCnt;
		m_tableList[m_tableCnt].m_desc = *desc;
		storedDesc = &m_tableList[m_tableCnt].m_desc;
		strcpy(m_tableList[m_tableCnt].m_tableName, name);
		m_tableCnt++;
	}
	return ret;
}

int32_t SchemaMgr::getTableId(const char* name, int32_t& tableId) {

	int32_t ret = NOTFOUND;

	for (int i = 0; i < m_tableCnt; ++i) {

		if (0 == strcmp(name, m_tableList[i].m_tableName)) {

			tableId = i;
			ret = SUCCESS;
			break;
		}
	}
	return ret;
}

} /* namespace expdb */

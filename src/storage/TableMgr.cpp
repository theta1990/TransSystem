/*
 * TableMgr.cpp
 *
 *  Created on: Jan 9, 2015
 *      Author: volt
 */

#include "TableMgr.h"
#include "../common.h"
namespace expdb {

TableMgr * TableMgr::ins__ = NULL;

TableMgr* TableMgr::getInstance() {

	if( NULL == ins__ ){
		ins__ = new TableMgr();
	}
	return ins__;
}

int32_t TableMgr::getTable(int32_t id, RowTable*&table) {

	if( m_Count <= id ) return ERROR;
	if( m_flags[id] == 0 ) {	//deleted
		return ERROR;
	}else {
		table = m_tableList[id];
		return SUCCESS;
	}
}

int32_t TableMgr::createTable(const RowDesc* desc, int32_t &id) {

	id = atomic::atomic_inc(&m_Count);

	m_flags[id] = 1;

	RowTable *table = new RowTable();
	table->setDesc(desc);
	m_tableList[id] = table;

	return SUCCESS;
}

TableMgr::TableMgr() {
	// TODO Auto-generated constructor stub
	m_flags.clear();
	m_tableList.clear();
	m_Count = 0;
}

TableMgr::~TableMgr() {
	// TODO Auto-generated destructor stub
}

} /* namespace expdb */

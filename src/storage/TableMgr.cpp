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

	int32_t ret = SUCCESS;
	if( id >= maxTableNum ){

		ret = ERROR;
	}else if( m_flag[id] != 0 ){
		table = m_tableList[id];
		ret = SUCCESS;
	}else {
		ret=  ERROR;
	}
	return ret;
}

int32_t TableMgr::createTable(const RowDesc* desc, int32_t &id) {

	ScopedLock guard(m_lock);
//	id = atomic::atomic_inc(&m_Count);

//	m_flags[id] = 1;

	RowTable *table = new RowTable();
	table->setDesc(desc);
	int8_t i;
	for(i = 0; i<maxTableNum; ++i){
		if( m_flag[i] == 0 ) break;
	}
	if( i != maxTableNum ){
		m_tableList[i] = table;
		m_flag[i] = 1;
		id = i;
		return SUCCESS;
	}else {
		VOLT_WARN("Table count reaches upper bound, %d", maxTableNum);
		return ERROR;
	}
}

TableMgr::TableMgr() {
	// TODO Auto-generated constructor stub
//	m_flags.clear();
//	m_tableList.clear();
//	m_Count = 0;
	m_lock.reset();
}

TableMgr::~TableMgr() {
	// TODO Auto-generated destructor stub
}

} /* namespace expdb */

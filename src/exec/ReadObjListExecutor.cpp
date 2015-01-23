/*
 * ReadObjListExecutor.cpp
 *
 *  Created on: Jan 13, 2015
 *      Author: volt
 */

#include "ReadObjListExecutor.h"

namespace expdb {

ReadObjListExecutor::ReadObjListExecutor() :
		m_objList(), m_desc(NULL), m_pos(0) {

	m_objList.clear();
}

ReadObjListExecutor::~ReadObjListExecutor() {
	// TODO Auto-generated destructor stub
}

int32_t ReadObjListExecutor::open() {

	int32_t ret = SUCCESS;
	m_pos = 0;
	if (m_desc == NULL) {
		ret = ERROR;
		VOLT_WARN("Row description is not set");
	}
	return ret;
}

int32_t ReadObjListExecutor::next(const Row *&row) {

	int32_t ret = SUCCESS;
	uint32_t i;
	m_curRow->setDesc(m_desc);
	for(i = 0; i < m_desc->getColCnt() && m_pos < m_objList.size(); ++i, ++m_pos){

		if( m_desc->getRowtype(i) != m_objList[m_pos].getType() ){

			VOLT_DEBUG("Input type %d does not match the schema %d", m_objList[m_pos].getType(), m_desc->getRowtype(i));
			ret = ERROR;		//input now match the schema
			break;
		}
		m_curRow->setCol(i, m_objList[m_pos]);
	}


	if( SUCCESS == ret ) {

		if( i != m_desc->getColCnt() ){

			ret = END;
		}else {

			row = m_curRow;
		}
	}
	return ret;
}

int32_t ReadObjListExecutor::close() {

	m_pos = m_objList.size();
	return SUCCESS;
}

int32_t ReadObjListExecutor::reset() {

	m_pos = 0;
	return SUCCESS;
}

int32_t ReadObjListExecutor::setDesc(const RowDesc *desc) {

	m_desc = desc;
	return SUCCESS;
}

int32_t ReadObjListExecutor::addObjList(RowObj *list, int32_t size) {

	int32_t ret = SUCCESS;

	for (int32_t i = 0; i < size; ++i) {
		m_objList.push_back(list[i]);
	}
	return ret;
}

int32_t ReadObjListExecutor::addObjList(std::vector<RowObj> list) {

	int32_t ret = SUCCESS;

	for (std::vector<RowObj>::iterator it = list.begin(); it != list.end();
			it++) {

		m_objList.push_back(*it);
	}
	return ret;
}

int32_t ReadObjListExecutor::addObj(RowObj obj) {

	int32_t ret = SUCCESS;

	m_objList.push_back(obj);
	return ret;
}

} /* namespace expdb */

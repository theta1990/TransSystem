/*
 * ReadExecutor.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: volt
 */

#include "ReadExecutor.h"

namespace expdb {

ReadExecutor::ReadExecutor() : m_str(NULL), m_len(0), m_pos(0), m_desc(NULL){

}

int32_t ReadExecutor::open() {

	int32_t ret = SUCCESS;

	if( NULL == m_desc ){

		VOLT_DEBUG("desc is not provided");
		ret = ERROR;
	}else if ( NULL == m_str || m_len <= 0){

		VOLT_DEBUG(("input string is not given"));
		ret = ERROR;
	}else {
		m_pos = 0;
	}
	m_curRow->setDesc(m_desc);
	return ret;
}

int32_t ReadExecutor::next(const Row*& row) {

	int32_t ret = SUCCESS;
//	Row *tmpRow = (Row *)m_alloc->alloc(sizeof(Row));
	if( SUCCESS != m_curRow[0].deserilization(m_str, m_len, m_pos) ) {

		VOLT_DEBUG("deserilization reach end while reading row from input str");
		ret = END;		//reach the end of input string
	}else {
		m_curRow[0].setDesc(m_desc);
		row = m_curRow;
	}
	return ret;
}

int32_t ReadExecutor::close() {

	//TODO free the alloc memory
	m_pos = 0;
	return SUCCESS;
}

int32_t ReadExecutor::reset() {

	m_pos = 0;
	return SUCCESS;
}

} /* namespace expdb */


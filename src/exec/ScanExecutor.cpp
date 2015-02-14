/*
 * ScanExecutor.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: volt
 */

#include "ScanExecutor.h"

namespace expdb {

ScanExecutor::ScanExecutor(const RowTable *table) : m_table(table), m_it(m_table->getTableIterator()) {

}

int32_t ScanExecutor::open() {

	int32_t ret = SUCCESS;

	if( NULL == m_table ){

		VOLT_WARN("scan table is not set");
		ret = ERROR;
	}else {

		m_it = m_table->getTableIterator();
		ret = m_it.open();
	}

	return ret;
}

int32_t ScanExecutor::next(const Row *&row){

	int32_t ret = SUCCESS;

	ret = m_it.next(m_row);

	if( SUCCESS == ret ) {

		row = &m_row;
	}
	return ret;
}

int32_t ScanExecutor::close() {

	int32_t ret = SUCCESS;
	ret = m_it.close();
	return ret;
}


ScanExecutor::~ScanExecutor() {

}

} /* namespace expdb */

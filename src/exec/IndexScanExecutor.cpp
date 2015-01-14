/*
 * IndexScanExecutor.cpp
 *
 *  Created on: Jan 13, 2015
 *      Author: volt
 */

#include "IndexScanExecutor.h"

namespace expdb {

IndexScanExecutor::IndexScanExecutor() :
		m_key(), m_table(NULL) {

}

IndexScanExecutor::~IndexScanExecutor() {
	// TODO Auto-generated destructor stub
}

int32_t IndexScanExecutor::open() {

	int32_t ret = SUCCESS;

	if ( NULL == m_table) {
		ret = ERROR;
		VOLT_DEBUG("table is not set");
	}
	return ret;
}

int32_t IndexScanExecutor::next(const Row *&nextRow) {

	int32_t ret = SUCCESS;

	if (SUCCESS != (ret = const_cast<RowTable*>(m_table)->get(m_key, m_row))) {

		VOLT_DEBUG("does not find key in the table");
	} else {
		nextRow = &m_row;
	}

	return ret;
}

int32_t IndexScanExecutor::close(){
	int32_t ret = SUCCESS;

	return SUCCESS;
}

} /* namespace expdb */

/*
 * IndexScanExecutor.cpp
 *
 *  Created on: Jan 13, 2015
 *      Author: volt
 */

#include "IndexScanExecutor.h"

namespace expdb {

IndexScanExecutor::IndexScanExecutor() :
		m_key(), m_table(NULL), m_pos(0) {

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

	if (m_pos == 0) {

		if (SUCCESS
				!= (ret = const_cast<RowTable*>(m_table)->get(m_key, m_row))) {

			VOLT_DEBUG("Does not find key in the table, %d", ret);
//			ret = END;
		} else {
			nextRow = &m_row;
		}
		++m_pos;
	} else {
		ret = END;
	}
	return ret;
}

int32_t IndexScanExecutor::close() {

	return SUCCESS;
}

} /* namespace expdb */

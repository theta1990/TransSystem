/*
 * GetExecutor.cpp
 *
 *  Created on: Dec 24, 2014
 *      Author: volt
 */

#include "GetExecutor.h"

namespace expdb {

GetExecutor::GetExecutor() : m_table(NULL), m_child(NULL), m_curRow() {
	// TODO Auto-generated constructor stub

}

GetExecutor::~GetExecutor() {
	// TODO Auto-generated destructor stub
	m_table = NULL;
	m_child = NULL;
}

int32_t GetExecutor::open() {

	int32_t ret = SUCCESS;

	if ( NULL == m_child || NULL == m_table ) {
		ret = ERROR;
		VOLT_DEBUG("child operation or table is not set");
	} else if (SUCCESS != (ret = m_child->open())) {

		VOLT_DEBUG("child open failed");
	}

	return ret;
}

/**
 *	next function read the next record in the table;
 */
int32_t GetExecutor::next(const Row*&nextRow) {

	int32_t ret = SUCCESS;
	const Row *row;

	while (true) {
		if (SUCCESS != (ret = m_child->next(row))) {

			VOLT_DEBUG("child op end");
			break;
		} else {

			RowKey key;
			row->getRowKey(key);
			if (SUCCESS
					!= (ret = const_cast<RowTable*>(m_table)->get(key, m_curRow))) {
				VOLT_DEBUG("does not find key in the table");
			} else {
				nextRow = &m_curRow;
				break;
			}
		}
	}
	return ret;
}

int32_t GetExecutor::close() {

	int32_t ret = SUCCESS;

	if( m_child != NULL && (SUCCESS != (ret = m_child->close()))){

		VOLT_ERROR("child op close failed");
	}
	return ret;
}

int32_t GetExecutor::addChild(Executor* child) {

	int32_t ret = SUCCESS;
	if (child == NULL || child == this) {
		VOLT_ERROR("child is null or child equals with self");
		ret = ERROR;
	} else {

		m_child = child;
	}
	return ret;
}

} /* namespace expdb */

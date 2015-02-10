/*
 * UpdateExecutor.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: volt
 */

#include "UpdateExecutor.h"

namespace expdb {

UpdateExecutor::UpdateExecutor() :
		m_childop(NULL), m_curRow(NULL), m_exp(), m_table(NULL) {

}

UpdateExecutor::~UpdateExecutor() {

	m_childop = NULL;
	m_curRow = NULL;
}

int32_t UpdateExecutor::open() {

	int ret = SUCCESS;

	if ( NULL == m_childop || NULL == m_table) {
		VOLT_INFO("update executor is not set properly");
		ret = ERROR;
	} else if (SUCCESS != (ret = m_childop->open())) {

		VOLT_INFO("child op open failed");
	} else {

		while ( SUCCESS == ret) {

			if (SUCCESS == (ret = m_childop->next(m_curRow))) {
//				m_exp->cal(m_curRow, m_curRow);	//calculate the update version
				RowKey key;
				m_curRow->getRowKey(key);

				PhyPlan* plan = getPhyPlan();
				TaskContext* ctx;
				if (plan == NULL) {
					VOLT_WARN("Physical plan is not set");
					ret = ERROR;
				} else if ((ctx = plan->getTaskContext()) == NULL) {
					VOLT_WARN("Context is not set");
					ret = ERROR;
				} else if (SUCCESS
						!= (ret = m_table->update(*ctx, key, &m_exp))) {	//如果一个元素更新失败，后面的数据更新都不会进行
					VOLT_WARN("Update failed");
				}
			}
		}

		if( END == ret ) {
			ret = SUCCESS;
		}
	}
	return ret;
}

int32_t UpdateExecutor::next(const Row*& row) {

	UNUSED(row);
	return END;
}

int32_t UpdateExecutor::close() {

	m_curRow = NULL;
	return SUCCESS;
}

int32_t UpdateExecutor::addChild(Executor* childop) {

	m_childop = childop;
	return SUCCESS;
}

} /* namespace expdb */


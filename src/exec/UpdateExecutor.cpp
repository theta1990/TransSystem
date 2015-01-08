/*
 * UpdateExecutor.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: volt
 */

#include "UpdateExecutor.h"

namespace expdb {

UpdateExecutor::UpdateExecutor() :
		m_childop(NULL), m_curRow(NULL), m_exp(NULL), m_table(NULL) {

}

UpdateExecutor::~UpdateExecutor() {

	m_childop = NULL;
	m_curRow = NULL;
}

int32_t UpdateExecutor::open() {

	int ret = SUCCESS;

	if ( NULL == m_childop || NULL == m_table ) {
		VOLT_INFO("update executor is not set properly");
		ret = ERROR;
	} else if (SUCCESS != (ret = m_childop->open())) {

		VOLT_INFO("child op open failed");
	} else {

		while (true) {

			if (m_childop->next(m_curRow) != END) {
//				m_exp->cal(m_curRow, m_curRow);	//calculate the update version
				RowKey key;
				m_curRow->getRowKey(key);
				if ( NULL == m_exp) {

					VOLT_DEBUG("update expression is not set");
					break;
				} else {

					PhyPlan* plan = getPhyPlan();
					TaskContext* ctx;
					if( plan == NULL ){
						VOLT_WARN("phyical plan is not set");
						ret = ERROR;
					}else if( (ctx = plan->getTaskContext()) == NULL ){
						VOLT_WARN("context is not set");
						ret = ERROR;
					}else if( SUCCESS != (ret = m_table->update(*ctx, key, m_exp)) ){
						VOLT_WARN("update fail");
					}
				}
			} else {
				break;
			}
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


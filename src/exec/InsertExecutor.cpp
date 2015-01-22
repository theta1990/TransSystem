/*
 * InsertExecutor.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: volt
 */

#include "InsertExecutor.h"
#include "../storage/Row.h"
namespace expdb {

InsertExecutor::InsertExecutor() :
		m_child(NULL), m_table(NULL) {

}

int32_t InsertExecutor::open() {

	int32_t ret = SUCCESS;

	const Row *row = NULL;

	if (m_table == NULL || m_child == NULL) {
		VOLT_DEBUG("insert executor is not inited properly");
		ret = ERROR;
	} else if (SUCCESS == (ret = m_child->open())) {
		TaskContext* ctx;
		PhyPlan *plan = getPhyPlan();
		if ( NULL == plan) {
			VOLT_WARN("phy plan is not set");
			ret = ERROR;
		} else if ((ctx = plan->getTaskContext()) == NULL) {
			VOLT_WARN("transaction context is not set");
			ret = ERROR;
		} else {
			while (true) {
				if (SUCCESS != m_child->next(row)) {
					break;
				} else {

					if (SUCCESS != (ret = m_table->insert(*ctx, row))) {
						VOLT_WARN("insert fails");
						row->dump();
						break;
					}else {
						VOLT_INFO("insert success");
						row->dump();
					}
				}
			}
		}
	}
	return ret;
}

int32_t InsertExecutor::next(const Row *&row) {

	UNUSED(row);
	return END;
}

int32_t InsertExecutor::close() {

	m_child->close();
	return SUCCESS;
}

} /* namespace expdb */

/*
 * StoredProcedure.cpp
 *
 *  Created on: Feb 4, 2015
 *      Author: volt
 */

#include "StoredProcedure.h"
#include "../exec/Executor.h"
#include "../exec/PhyPlan.h"
#include "../exec/PhyPlanFactory.h"
namespace expdb {

StoredProcedure::StoredProcedure() {
	// TODO Auto-generated constructor stub

}

int32_t StoredProcedure::executePhyPlan(PhyPlan &plan, TaskContext *ctx,
		ResultSet *&results) {

	int32_t ret = SUCCESS;
	const Row *row;
	if ( NULL == ctx) {
		VOLT_DEBUG("transaction context is not provided");
	} else {

		plan.setContext(ctx);
		Executor *exec = plan.getQuery();
		if ( NULL != exec && SUCCESS == (ret = exec->open())) {

			while (SUCCESS == (ret = exec->next(row))) {

				results->addRow(*row);
			}
		}

		if (END != ret) {
			if (SUCCESS == ctx->getRetCode()) {
				VOLT_ERROR("Context ret code is not proper");
				ctx->setErrorCode(ERROR);
			}
		}
	}
	return ret;
}

StoredProcedureTask::StoredProcedureTask() :
		m_objList(NULL), m_size(0), m_spRef(NULL), m_tranId(0), m_ctx(NULL), m_alloc(
		NULL) {

}

StoredProcedureTask::StoredProcedureTask(StoredProcedure *spRef,
		RowObj *objList, uint32_t sz) :
		m_objList(objList), m_size(sz), m_spRef(spRef), m_tranId(0), m_ctx(
				NULL), m_alloc(NULL) {

}

int32_t StoredProcedureTask::run() {

	int32_t ret = SUCCESS;

	if (SUCCESS
			!= (ret = TaskContextMgr::getInstance()->newContext(m_tranId, m_ctx,
					*m_alloc))) {

		VOLT_ERROR("Create transaction context failed");
	} else {

		m_ctx->startProcess();

		m_spRef->run(m_objList, m_size, m_ctx);

		ret = m_ctx->getRetCode();		//run 的返回结果要如何处理呢？
		if (SUCCESS != ret) {
			m_ctx->rollback();
		} else {
			m_ctx->commit();
		}

		m_ctx->postProcess();
		TaskContextMgr::getInstance()->releaseContext(m_ctx, *m_alloc);
	}
	return ret;
}
} /* namespace expdb */

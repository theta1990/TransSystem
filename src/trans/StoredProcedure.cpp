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

/**
 * 实际执行一次计划
 * 返回执行是否成功
 * 在TaskContex中附上访问数据库时发生的错误原因，如果有的话
 */
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

		if (END != ret) {	//执行实际是失败了
			if (SUCCESS == ctx->getRetCode()) {
				//可能失败的原因不是在访问数据库的时候发生的，而是一些系统错误，在这里统一处理。
//				VOLT_ERROR("Context ret code is not proper");
				ctx->setErrorCode(ERROR);
			}
		}else {
			ret = SUCCESS;
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

/**
 * 返回值：
 * SUCCESS 存储过程被成功执行
 * ERROR   存储过程遇到一些系统错误
 * DBERROR 存储过程遇到一些数据库访问错误
 * REEXEC  存储过程访问的数据被占用，可以重新执行
 * 	如果是因为lock acquire fail导致的错误应该是可以重启的。
 */
int32_t StoredProcedureTask::run() {

	int32_t ret = SUCCESS;
	int32_t ctxCode = SUCCESS;
	int32_t rc = SUCCESS;
	if (SUCCESS
			!= (ret = TaskContextMgr::getInstance()->newContext(m_tranId, m_ctx,
					*m_alloc))) {

		VOLT_ERROR("Create transaction context failed");
	} else {

		m_ctx->startProcess();

		ret = m_spRef->run(m_objList, m_size, m_ctx);
		ctxCode = m_ctx->getRetCode();

		if (SUCCESS != ret) {

			m_ctx->rollback();
			switch (ctxCode) {
			case SUCCESS:
				VOLT_ERROR("It can be here");
				rc = ERROR;
				break;
			case CTX_LOCK_CONFLICT:
				rc = REEXEC;
				break;
			case CTX_ROW_NOT_EXIST:
				rc = DBERROR;
				break;
			case ERROR:
				rc = ERROR;
				break;
			default:
				VOLT_ERROR("un-handle case, it can be here");
				rc = ERROR;
				break;
			}
		} else {
			m_ctx->commit();
			if( ctxCode != SUCCESS ){
				VOLT_ERROR("It can be here");
			}
		}

		m_ctx->postProcess();
		TaskContextMgr::getInstance()->releaseContext(m_ctx, *m_alloc);
	}
	return rc;
}
} /* namespace expdb */

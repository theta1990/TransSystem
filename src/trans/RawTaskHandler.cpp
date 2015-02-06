/*
 * RawTaskHandler.cpp
 *
 *  Created on: Feb 4, 2015
 *      Author: volt
 */

#include "RawTaskHandler.h"
#include "../common.h"
#include "../storage/Row.h"
#include "TaskContext.h"
#include "../exec/Executor.h"
namespace expdb {

RawTaskHandler::RawTaskHandler() :
		m_queue(128), m_done(false), m_stat() {

}

int RawTaskHandler::push(RawTask &task) {

	int retry_times = 10;
	while (!m_queue.push(task) && (retry_times--) > 0)
		;

	return retry_times > 0 ? SUCCESS : ERROR;
}

void RawTaskHandler::work() {

	RawTask task;

	m_stat.start();

//	printf("-thread %d start at %ld\n", m_pid, getCycleCount());
	while (!m_done) {

		while (m_queue.pop(task)) {
			//process the task here
			if (TRAN_FINISHED == handleTask(task))
				m_stat.m_throughput++;
		}

	}

	while (m_queue.pop(task)) {
		//process the task here
		if (TRAN_FINISHED == handleTask(task))
			m_stat.m_throughput++;

	}

	m_stat.stop();

//	VOLT_INFO("Thread %d exited with %d task processed\n", m_pid, m_cnt);
//	printf("thread %d exited with %d handle\n", m_pid, m_cnt);
}
int RawTaskHandler::handleTask(RawTask& rawtask) {

	PhyPlan *plan = NULL;
	unsigned int tid;
	TaskContext *ctx;
	TransTask task;
	const Row *row;
	int rc;

	if (SUCCESS != (rc = rawtask.parse(task))) {

		VOLT_INFO("parser error");
	} else {
		tid = task.getTranId();
	}

	if (rc == SUCCESS) {
		if (SUCCESS
				== TaskContextMgr::getInstance()->newContext(tid, ctx,
						m_alloc)) {

			ctx->startProcess();

			while (true) {

				if ( NULL == (plan = task.getNextPlan())) {
					VOLT_DEBUG("task processed");
					break;
				} else {

					plan->setContext(ctx);

					Executor *exec = plan->getQuery();
					if ( NULL != exec && SUCCESS == (rc = exec->open())) {
						while (SUCCESS == (rc = exec->next(row)))
							//here we can set response
							;
					}

					if (END != rc) {

						if (SUCCESS == ctx->getRetCode()) {
							VOLT_ERROR("Context ret code is not set properly");
							ctx->setErrorCode(ERROR);
						}
						break;
					}
				}
			}

			rc = ctx->getRetCode();
			if (SUCCESS != rc) {
				ctx->rollback();
			} else {
				ctx->commit();
			}

			ctx->postProcess();

			TaskContextMgr::getInstance()->releaseContext(ctx, m_alloc);
			if (SUCCESS == rc) { //transaction successfully processed

				VOLT_INFO("Successfully handle trans %d", task.getTranId());
				task.destroy();
				rawtask.destroy();
			} else if (LOCK_CONFLICT == rc) {

				VOLT_WARN("Trans[%d] failed due to lock conflict",
						task.getTranId());
				task.destroy();
				m_queue.push(rawtask);
			} else {	//re-process the transaction

				VOLT_WARN("Trans failed due to error[%d]", rc);
				task.destroy();
				rawtask.destroy();
//			m_queue.push(task);		//这里写的肯定简单了
			}
		}
	}
	return SUCCESS;
}

void RawTaskHandler::stop() {

	m_done = true;
}

RawTaskHandler::~RawTaskHandler() {
	// TODO Auto-generated destructor stub
}

} /* namespace expdb */

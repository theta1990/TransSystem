/*
 * ProcedureHandler.cpp
 *
 *  Created on: Feb 6, 2015
 *      Author: volt
 */

#include "ProcedureHandler.h"
#include "../common.h"
namespace expdb {

ProcedureHandler::ProcedureHandler() : m_queue(128), m_done(false), m_stat() {

}

int ProcedureHandler::push(StoredProcedureTask &task) {

	int retry_times = 10;
	while (!m_queue.push(task) && (retry_times--) > 0)
		;

	return retry_times > 0 ? SUCCESS : ERROR;
}


void ProcedureHandler::work() {

	StoredProcedureTask task;

	m_stat.start();

//	printf("-thread %d start at %ld\n", m_pid, getCycleCount());
	while (!m_done) {

		while (m_queue.pop(task)) {
			//process the task here
//			if (TRAN_FINISHED == handleTask(task))
//				m_stat.m_throughput++;
			handleTask(task);
		}

	}

	while (m_queue.pop(task)) {
		//process the task here
//		if (TRAN_FINISHED == handleTask(task))
//			m_stat.m_throughput++;
		handleTask(task);
	}

	m_stat.stop();

//	VOLT_INFO("Thread %d exited with %d task processed\n", m_pid, m_cnt);
//	printf("thread %d exited with %d handle\n", m_pid, m_cnt);
}

int ProcedureHandler::handleTask(StoredProcedureTask& task) {

	int rc;

	rc = task.run();

	if (rc == SUCCESS) {

		if (SUCCESS == rc) { //transaction successfully processed

			VOLT_INFO("Successfully handle trans %d", task.getTranId());
			m_stat.incTaskCount(task.getProcedureName());
			task.destroy();
		} else if (LOCK_CONFLICT == rc) {

			VOLT_WARN("Trans[%d] failed due to lock conflict", task.getTranId());
			m_stat.incRetryTaskCount(task.getProcedureName());
			task.destroy();
			m_queue.push(task);
		} else {	//re-process the transaction

			VOLT_WARN("Trans failed due to error[%d]", rc);
			m_stat.incRetryTaskCount(task.getProcedureName());
			task.destroy();
		}
	}
	return SUCCESS;
}

void ProcedureHandler::stop() {

	m_done = true;
}

ProcedureHandler::~ProcedureHandler() {
	// TODO Auto-generated destructor stub
}

} /* namespace expdb */
;

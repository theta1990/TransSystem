/*
 * TaskContext.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: volt
 */

#include "TaskContext.h"
#include "../common.h"
namespace expdb {

TaskContextMgr* TaskContextMgr::ins_ = NULL;

TaskContext::TaskContext() :
		m_cbTaskList(), m_undoTaskList(), m_lock(NULL), m_logger(NULL), m_transId(
				0), m_rollback(false), m_retCode(SUCCESS) {
	// TODO Auto-generated constructor stub
}

TaskContext::~TaskContext() {
	// TODO Auto-generated destructor stub
}

int32_t TaskContext::handleLockFailure() {

	int32_t ret = SUCCESS;

	//try to roll back here;

	return ret;
}

int32_t TaskContext::rollback() {

	int32_t ret = SUCCESS;
	m_rollback = true;
	VOLT_INFO("roll back trans: %d", m_transId);
	for (uint32_t i = 0; i < m_undoTaskList.size(); ++i) {
		if (SUCCESS != m_undoTaskList[i].undo()) {
			VOLT_ERROR("ops, undo failure, what is impossible!!");
		}
	}
//	for (uint32_t i = 0; i < m_cbTaskList.size(); ++i) {
//		if (SUCCESS != m_cbTaskList[i].callback()) {
//			VOLT_DEBUG("roll back, unlock failed");
//		}
//	}
	return ret;
}

/**
 * possible, we can get all the lock here
 */
int32_t TaskContext::startProcess() {

	m_rollback = false;
	m_cbTaskList.clear();
	return SUCCESS;
}

int32_t TaskContext::postProcess() {

	int32_t ret = SUCCESS;

//	if (!m_rollback) {

	for (uint32_t i = 0; i < m_cbTaskList.size(); ++i) {
		if (SUCCESS != m_cbTaskList[i].callback()) {
			VOLT_DEBUG("post process, unlock failed");
		}
	}
//	}
	return ret;
}

TaskContextMgr * TaskContextMgr::getInstance() {

	if (ins_ == NULL) {
		ins_ = new TaskContextMgr();
	}
	return ins_;
}

int32_t TaskContextMgr::newContext(int32_t tid, TaskContext*& ctx,
		Allocator& alloc) {

	int32_t ret = SUCCESS;

	LockInfo *lock;
	Logger *logger;
	void *p = alloc.alloc(sizeof(TaskContext));
	void *plock = alloc.alloc(sizeof(RCLockInfo));
	void *plogger = alloc.alloc(sizeof(Logger));
	ctx = new (p) TaskContext();
	lock = new (plock) RCLockInfo(ctx->m_cbTaskList);
	logger = new (plogger) Logger(alloc, ctx->m_undoTaskList);

	ctx->setLockInfo(lock);
	ctx->setLogger(logger);
	ctx->setTransId(tid);
	return ret;
}

int32_t TaskContextMgr::releaseContext(TaskContext *ctx, Allocator& alloc) {

	int32_t ret = SUCCESS;

	ctx->destroy(alloc);
	alloc.free(ctx);
	return ret;
}

} /* namespace expdb */


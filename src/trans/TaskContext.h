/*
 * TaskContext.h
 *
 *  Created on: Dec 16, 2014
 *      Author: volt
 */

#ifndef TASKCONTEXT_H_
#define TASKCONTEXT_H_

#include "LockInfo.h"
#include "../exec/PhyPlan.h"
#include "../common/memory/Allocator.h"
#include <map>
namespace expdb {

//typedef uint32_t Datum;
//typedef uint32_t Log;
//typedef uint32_t Dependency;

class LockInfo;
class PhyPlan;

class TaskContextMgr;

/**
 * 应该还需要一个undo list，将所有的修改回滚
 */
class TaskContext {
public:
	TaskContext();
	virtual ~TaskContext();

	int32_t setLockInfo(LockInfo *info) {
		m_lock = info;
		return SUCCESS;
	}
	int32_t getLockInfo(LockInfo *&info) {

		if ( NULL != m_lock) {
			info = m_lock;
			return SUCCESS;
		} else {

			return ERROR;
		}
	}
	int32_t handleLockFailure();
	int32_t rollback();

	int32_t startProcess();
	int32_t postProcess();

	int32_t getRetCode() {
		return m_retCode;
	}

	friend TaskContextMgr;
private:

	std::vector<CallbackTask> m_cbTaskList;		//解锁任务
//	Datum			data;		//数据，什么数据呢？延迟写的时候可能会用到的数据
//	Log				logs;		//日志，
//	Dependency		dep;		//提交依赖，如果采用投机执行之后会需要用到
	LockInfo* m_lock;
	int32_t m_transId;
	bool	m_rollback;
	int32_t m_retCode;
};

/**
 * 跟是事务id维护所有事务的执行上下文
 */
class TaskContextMgr {
public:

	static TaskContextMgr * getInstance();
	int32_t newContext(int32_t tid, TaskContext *&, Allocator &);
	int32_t releaseContext(TaskContext *, Allocator &);
private:

	static TaskContextMgr *ins_;
};

} /* namespace expdb */

#endif /* TASKCONTEXT_H_ */

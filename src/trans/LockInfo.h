/*
 * LockInfo.h
 *
 *  Created on: Dec 16, 2014
 *      Author: volt
 */

#ifndef LOCKINFO_H_
#define LOCKINFO_H_

#include <vector>
#include "../common.h"
#include "QLock.h"
#include "UndoTask.h"
#include "../storage/RowTable.h"
namespace expdb {

class CallbackTask;

/**
 * lock before execution
 * unlock after finished, add a unlock task
 */
class LockInfo {
public:
	LockInfo();

	virtual int32_t transBegin() = 0;
	virtual int32_t readBegin(RowValue *&value) = 0;
	virtual int32_t writeBegin(RowValue *&value) = 0;

	virtual ~LockInfo();
};

class RCLockInfo: public LockInfo {

public:
	RCLockInfo(std::vector<CallbackTask> &cbTasks);

	virtual int32_t transBegin();
	virtual int32_t readBegin(RowValue *&value);
	virtual int32_t writeBegin(RowValue *&value);

	virtual ~RCLockInfo();
private:

	std::vector<CallbackTask> &m_cbTasks;
//	std::vector<UndoTask> 	&m_undoTasks;
};

/**
 * 理论上还要记录数据原始的取值
 */
class CallbackTask {
public:

	CallbackTask(RowValue *value) {

		m_value = value;
	}

	virtual int32_t callback() {

		if ( SUCCESS == m_value->m_lock.unlock())
			return SUCCESS;
		else
			return ERROR;
	}

	virtual ~CallbackTask() {

	}
protected:

	RowValue *m_value;
};

} /* namespace expdb */

#endif /* LOCKINFO_H_ */

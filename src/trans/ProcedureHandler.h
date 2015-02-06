/*
 * ProcedureHandler.h
 *
 *  Created on: Feb 6, 2015
 *      Author: volt
 */

#ifndef PROCEDUREHANDLER_H_
#define PROCEDUREHANDLER_H_

#include "TaskQueue.h"
#include "LockMgr.h"
#include "../common/memory/Allocator.h"
#include "../StatCollector.h"
#include "StoredProcedure.h"
#include <boost/lockfree/queue.hpp>
#include <boost/atomic/atomic.hpp>

namespace expdb {

class ProcedureHandler : public TaskQueue {

public:
	ProcedureHandler();
	virtual ~ProcedureHandler();
	StatCollector & getStat();
	int push(StoredProcedureTask &spTask);
	virtual void work();
	virtual int handleTask(StoredProcedureTask &spTask);
	virtual void stop();
private:
	boost::lockfree::queue<StoredProcedureTask> m_queue;
	boost::atomic<bool> m_done;
	StatCollector m_stat;
	Allocator m_alloc;
};

} /* namespace expdb */

#endif /* PROCEDUREHANDLER_H_ */

/*
 * TransExecQueue.h
 *
 *  Created on: Dec 5, 2014
 *      Author: volt
 */

#ifndef TRANSEXECQUEUE_H_
#define TRANSEXECQUEUE_H_

#include "TaskQueue.h"
#include "TransTask.h"
#include "LockMgr.h"
#include "../common/memory/Allocator.h"
#include "../StatCollector.h"
//#include <queue>
#include <boost/lockfree/queue.hpp>
#include <boost/atomic/atomic.hpp>

namespace expdb {

class TransExecQueue: public TaskQueue {

public:
	TransExecQueue();
	StatCollector & getStat();
	int push(TransTask task);
//	void setLockMgr(LockMgr *lockmgr);
	virtual void work();
	virtual int handleTask(TransTask &task);
	virtual void stop();
	virtual ~TransExecQueue();
private:
	boost::lockfree::queue<TransTask> m_queue;
//	std::queue<TransTask> m_queue;
	boost::atomic<bool> m_done;
//	LockMgr *m_lockMgr;
	StatCollector m_stat;

	Allocator	m_alloc;
};

} /* namespace expdb */

#endif /* TRANSEXECQUEUE_H_ */

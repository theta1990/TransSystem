/*
 * RawTaskHandler.h
 *
 *  Created on: Feb 4, 2015
 *      Author: volt
 */

#ifndef RAWTASKHANDLER_H_
#define RAWTASKHANDLER_H_
#include "TaskQueue.h"

#include "TransTask.h"
#include "LockMgr.h"
#include "../common/memory/Allocator.h"
#include "../StatCollector.h"
//#include <queue>
#include <boost/lockfree/queue.hpp>
#include <boost/atomic/atomic.hpp>
namespace expdb {

class RawTaskHandler: public TaskQueue {

public:
	RawTaskHandler();
	virtual ~RawTaskHandler();
	StatCollector & getStat();
	int push(RawTask &task);
//	void setLockMgr(LockMgr *lockmgr);
	virtual void work();
	virtual int handleTask(RawTask &rawtask);
	virtual void stop();
private:
	boost::lockfree::queue<RawTask> m_queue;
	boost::atomic<bool> m_done;
	StatCollector m_stat;
	Allocator m_alloc;
};

}
/* namespace expdb */

#endif /* RAWTASKHANDLER_H_ */

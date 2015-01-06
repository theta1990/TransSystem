/*
 * TaskQueue.h
 *
 *  Created on: Dec 5, 2014
 *      Author: volt
 */

#ifndef TASKQUEUE_H_
#define TASKQUEUE_H_

#include <pthread.h>
namespace expdb {

class TaskQueue {
public:
	TaskQueue();

	static void* run(void *);
	void start();
	virtual void work() = 0;
	void join();
	virtual ~TaskQueue();

protected:

	pthread_t m_pid;
};

} /* namespace expdb */

#endif /* TASKQUEUE_H_ */

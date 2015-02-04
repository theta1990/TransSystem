/*
 * MyServer.h
 *
 *  Created on: Jan 6, 2015
 *      Author: volt
 */

#ifndef MYSERVER_H_
#define MYSERVER_H_
#include "TransExecQueue.h"
#include "RawTaskHandler.h"
namespace expdb {

#define MaxWorkerThread 8
#define DefaultWorkerThread 8
class MyServer {
public:
	MyServer();
	virtual ~MyServer();

	int32_t startServer();
	int32_t handleTask(TransTask task);
	int32_t handleTask(RawTask task);

	int32_t exit();
	int32_t waitForExit();
private:

//	TransExecQueue*	m_threadPools[MaxWorkerThread];
	RawTaskHandler *m_threadPools[MaxWorkerThread];
	int32_t			m_count;
	Allocator		m_alloc;
};

} /* namespace expdb */

#endif /* MYSERVER_H_ */

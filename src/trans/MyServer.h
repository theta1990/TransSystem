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
#include "ProcedureHandler.h"
namespace expdb {

#define MaxWorkerThread 8
#define DefaultWorkerThread 1
class MyServer {
public:
	MyServer();
	virtual ~MyServer();

	int32_t startServer();
	int32_t handleTask(TransTask task);
	int32_t handleTask(RawTask task);
	int32_t handleTask(StoredProcedureTask task);
	int32_t exit();
	int32_t waitForExit();


private:

//	TransExecQueue*	m_threadPools[MaxWorkerThread];
//	RawTaskHandler *m_threadPools[MaxWorkerThread];
	ProcedureHandler *m_threadPools[MaxWorkerThread];
	int32_t			m_count;
	Allocator		m_alloc;

	void report() {

		StatCollector stat;
		stat.start();
		for(int threadidx = 0; threadidx < m_count; ++threadidx){
			stat.gather(m_threadPools[threadidx]->getStat());
		}
		stat.report();
	}

};

} /* namespace expdb */

#endif /* MYSERVER_H_ */

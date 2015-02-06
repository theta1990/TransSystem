/*
 * MyServer.cpp
 *
 *  Created on: Jan 6, 2015
 *      Author: volt
 */

#include "MyServer.h"

namespace expdb {

MyServer::MyServer() :
		m_count(DefaultWorkerThread), m_alloc() {

}

MyServer::~MyServer() {
	// TODO Auto-generated destructor stub
}

int32_t MyServer::startServer() {

	int32_t ret = SUCCESS;

	for (int i = 0; i < m_count; ++i) {

		m_threadPools[i] = new ProcedureHandler();
		m_threadPools[i]->start();
	}

	return ret;
}

/**
 * 这个函数可以考虑让多个线程同时调用，其作用就是让多个线程同时往队列中添加任务
 */
int32_t MyServer::handleTask(TransTask task) {

	int32_t ret = SUCCESS;

//	m_threadPools[rand()%m_count]->push(task);
//	UNUSED(task);

	return ret;
}

int32_t MyServer::handleTask(RawTask task){

	int32_t ret = SUCCESS;
//	m_threadPools[rand()%m_count]->push(task);
	return ret;
}

int32_t MyServer::handleTask(StoredProcedureTask task){

	m_threadPools[rand()%m_count]->push(task);
	return SUCCESS;
}

int32_t MyServer::exit(){

	for(int i=0;i<m_count;++i){
		m_threadPools[i]->stop();
	}
	return SUCCESS;
}

int32_t MyServer::waitForExit() {

	int32_t ret = SUCCESS;

	for(int i = 0;i<m_count;++i){
		m_threadPools[i]->join();
	}

	return ret;
}

} /* namespace expdb */

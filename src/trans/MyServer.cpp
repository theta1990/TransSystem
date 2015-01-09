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

	m_alloc.init(0);
}

MyServer::~MyServer() {
	// TODO Auto-generated destructor stub
}

int32_t MyServer::startServer() {

	int32_t ret = SUCCESS;

	for (int i = 0; i < m_count; ++i) {

		m_threadPools[i] = new TransExecQueue();
		m_threadPools[i]->start();
	}

	return ret;
}

int32_t MyServer::handleTask(TransTask task) {

	int32_t ret = SUCCESS;

	m_threadPools[rand()%m_count]->push(task);

	return ret;
}

} /* namespace expdb */

/*
 * Configure.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: volt
 */

#include "Configure.h"

namespace expdb {

Configure::Configure(): m_threadCnt(0), m_dbSize(0), m_taskSize(0) {

}

Configure::Configure(uint64_t threadCnt, uint64_t dbSize, uint64_t taskSize) :m_threadCnt(threadCnt), m_dbSize(dbSize), m_taskSize(taskSize){

}

Configure::~Configure() {
	// TODO Auto-generated destructor stub
}

uint64_t Configure::getThreadCnt() {

	return m_threadCnt;
}

uint64_t Configure::getDbSize() {

	return m_dbSize;
}

uint64_t Configure::getTaskSize() {

	return m_taskSize;
}

void Configure::setThreadCnt(uint64_t threadCnt) {

	m_threadCnt = threadCnt;
}

void Configure::setDbSize(uint64_t dbSize) {

	m_dbSize = dbSize;
}

void Configure::setTaskSize(uint64_t taskSize) {

	m_taskSize = taskSize;
}

void Configure::report() {

	printf("-ThreadCnt %ld\tDBSize %ld\tTaskSize %ld\r\n",
				getThreadCnt(), getDbSize(),
				getTaskSize());
}

} /* namespace expdb */

/*
 * StatCollector.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: volt
 */

#include "StatCollector.h"

namespace expdb {

StatCollector::StatCollector() :
		m_throughput(0), m_rollback(0), m_conflict(0), m_startCycle(0), m_stopCycle(
				0) {
	// TODO Auto-generated constructor stub
}

StatCollector::~StatCollector() {
	// TODO Auto-generated destructor stub
}

int StatCollector::gather(StatCollector& coll) {

	int ret = SUCCESS;

	m_throughput += coll.m_throughput;
	m_rollback += coll.m_rollback;
	m_conflict += coll.m_conflict;

	return ret;
}

int StatCollector::start() {

	m_startCycle = getCycleCount();
	gettimeofday(&m_starTime, NULL);

	return SUCCESS;
}

int StatCollector::stop() {

	m_stopCycle = getCycleCount();
	gettimeofday(&m_endTime, NULL);
	return SUCCESS;
}

void StatCollector::report() {


	printf("Throught %ld\tRollback %ld\tConflict %ld\tTime %ld\r\n",
			m_throughput, m_rollback, m_conflict,
			(m_stopCycle - m_startCycle) / 1000);
}

} /* namespace expdb */


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
				0), m_startms(0), m_endms(0), m_procedureCounts(), m_failedProcedureCounts(), m_retryProcedureCounts(), m_procNameSet() {
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

	m_startCycle = m_startCycle < coll.m_startCycle ?  m_startCycle : coll.m_startCycle;
	m_stopCycle = m_stopCycle > coll.m_stopCycle ? m_stopCycle : coll.m_stopCycle;

	m_startms = m_startms < coll.m_startms ? m_startms : coll.m_startms;
	m_endms = m_endms > coll.m_endms ? m_endms : coll.m_endms;

	for (std::set<std::string>::iterator procNameIter =
			coll.m_procNameSet.begin(); procNameIter != coll.m_procNameSet.end();
			procNameIter++) {

		m_procNameSet.insert(*procNameIter);

		m_procedureCounts[*procNameIter] += coll.m_procedureCounts[*procNameIter];
		m_failedProcedureCounts[*procNameIter] += coll.m_failedProcedureCounts[*procNameIter];
		m_retryProcedureCounts[*procNameIter] += coll.m_retryProcedureCounts[*procNameIter];
	}

	return ret;
}

int StatCollector::start() {

	m_startCycle = common::getCycleCount();
	m_startms = common::getTimeOfMs();
	return SUCCESS;
}

int StatCollector::stop() {

	m_stopCycle = common::getCycleCount();
	m_endms = common::getTimeOfMs();
	return SUCCESS;
}

void StatCollector::report() {

//	printf("Throught %ld\tRollback %ld\tConflict %ld\tTime %ld\r\n",
//			m_throughput, m_rollback, m_conflict,
//			(m_stopCycle - m_startCycle) / 1000);
	printf("============================================\n");
	printf("%10s\t%10s\t%10s\t%10s\n", "  ", "Processed", "Retried", "Failed");

	for (std::set<std::string>::iterator vIter = m_procNameSet.begin();
			vIter != m_procNameSet.end(); vIter++) {

		printf("%10s\t", vIter->c_str());
		printf("%10d\t", m_procedureCounts[*vIter]);
		printf("%10d\t", m_retryProcedureCounts[*vIter]);
		printf("%10d\n", m_failedProcedureCounts[*vIter]);
	}

	printf("\n");
	printf("\t-Throughput: %.2lf per sec\n",
			m_throughput / ((m_endms - m_startms) / 1000000.0));

	printf("============================================\n");
}

} /* namespace expdb */


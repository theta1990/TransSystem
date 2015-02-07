/*
 * StatCollector.h
 *
 *  Created on: Dec 6, 2014
 *      Author: volt
 */

#ifndef STATCOLLECTOR_H_
#define STATCOLLECTOR_H_
#include "../common.h"
#include "../clock.h"
#include "../debuglog.h"
#include "../Configure.h"
#include <sys/time.h>
#include <stdint.h>
#include <map>
#include <set>
namespace expdb {

class TransExecQueue;
class RawTaskHandler;
class ProcedureHandler;
class StatCollector {
public:
	StatCollector();
	virtual ~StatCollector();
	int gather(StatCollector &coll);

	int start();
	int stop();

	void report();

	void incTaskCount(std::string procName) {

		if (m_procedureCounts.find(procName) == m_procedureCounts.end()) {

			m_procedureCounts[procName] = 0;
			m_procNameSet.insert(procName);
		}
		m_procedureCounts[procName]++;
		m_throughput++;
	}

	void incFailedTaskCount(std::string procName) {

		if (m_failedProcedureCounts.find(procName) == m_procedureCounts.end()) {

			m_failedProcedureCounts[procName] = 0;
			m_procNameSet.insert(procName);
		}
		m_failedProcedureCounts[procName]++;
	}

	void incRetryTaskCount(std::string procName) {

		if (m_retryProcedureCounts.find(procName)
				== m_retryProcedureCounts.end()) {

			m_retryProcedureCounts[procName] = 0;
			m_procNameSet.insert(procName);
		}
		m_retryProcedureCounts[procName]++;
	}

	friend class TransExecQueue;
	friend class RawTaskHandler;
	friend class ProcedureHandler;
private:
	unsigned long	m_throughput;
	unsigned long	m_rollback;
	unsigned long	m_conflict;
	uint64_t		m_startCycle;
	uint64_t		m_stopCycle;
	uint64_t		m_startms;
	uint64_t		m_endms;
	std::map<std::string, uint32_t> m_procedureCounts;
	std::map<std::string, uint32_t> m_failedProcedureCounts;
	std::map<std::string, uint32_t> m_retryProcedureCounts;
	std::set<std::string>			m_procNameSet;
};

} /* namespace expdb */

#endif /* STATCOLLECTOR_H_ */

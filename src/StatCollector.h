/*
 * StatCollector.h
 *
 *  Created on: Dec 6, 2014
 *      Author: volt
 */

#ifndef STATCOLLECTOR_H_
#define STATCOLLECTOR_H_
#include "common.h"
#include "clock.h"
#include "debuglog.h"
#include "Configure.h"
#include <sys/time.h>
#include <stdint.h>
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
	friend class TransExecQueue;
	friend class RawTaskHandler;
	friend class ProcedureHandler;
private:
	unsigned long	m_throughput;
	unsigned long	m_rollback;
	unsigned long	m_conflict;
	uint64_t		m_startCycle;
	uint64_t		m_stopCycle;
	struct timeval	m_starTime;
	struct timeval 	m_endTime;

};

} /* namespace expdb */

#endif /* STATCOLLECTOR_H_ */

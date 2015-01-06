/*
 * Configure.h
 *
 *  Created on: Dec 6, 2014
 *      Author: volt
 */

#ifndef CONFIGURE_H_
#define CONFIGURE_H_
#include "common.h"
namespace expdb {

class Configure {
public:
	Configure();
	Configure(uint64_t threadCnt, uint64_t dbSize, uint64_t taskSize);
	virtual ~Configure();

	void setThreadCnt(uint64_t threadCnt);
	void setDbSize(uint64_t dbSize);
	void setTaskSize(uint64_t taskSize);

	uint64_t getThreadCnt();
	uint64_t getDbSize();
	uint64_t getTaskSize();

	void report();

private:
	uint64_t		m_threadCnt;
	uint64_t		m_dbSize;
	uint64_t		m_taskSize;
};

} /* namespace expdb */

#endif /* CONFIGURE_H_ */

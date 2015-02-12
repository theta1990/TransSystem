/*
 * Configure.h
 *
 *  Created on: Dec 6, 2014
 *      Author: volt
 */

#ifndef CONFIGURE_H_
#define CONFIGURE_H_
#include "common.h"
#include <string.h>
#include <stdlib.h>
namespace expdb {

class Configure {
public:

	static Configure *getInstance();

	Configure();
	Configure(uint32_t threadCnt, uint32_t dbSize, uint32_t taskSize);

	Configure(const char *filePath);

	virtual ~Configure();

	void setThreadCnt(uint32_t threadCnt);
	void setDbSize(uint32_t dbSize);
	void setTaskSize(uint32_t taskSize);

	uint32_t getThreadCnt();
	uint32_t getDbSize();
	uint32_t getTaskSize();

	void dump();

private:

	void parse(char *line) {

		char *whitePtr = NULL;

		if ( NULL != (whitePtr = strchr(line, ' '))) {

			*whitePtr++ = '\0';
			if( strcmp(line, "thread") == 0){

				m_threadCnt = strtoul(whitePtr, NULL ,10);
			} else if( strcmp(line, "dbsize") == 0) {

				m_dbSize = strtoul(whitePtr, NULL, 10);
			} else {

				printf("Parser configure file error, %s is not supported\n", line);
			}
		}
	}

	uint32_t		m_threadCnt;
	uint32_t		m_dbSize;
	uint32_t		m_taskSize;

	static Configure		*__ins;
	static const char				*__filePath;
};

} /* namespace expdb */

#endif /* CONFIGURE_H_ */

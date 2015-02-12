/*
 * Configure.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: volt
 */

#include "Configure.h"

namespace expdb {

Configure * Configure::__ins = NULL;
const char * Configure::__filePath = "configure.txt";

Configure * Configure::getInstance() {

	if (__ins == NULL) {
		//load configure
		__ins = new Configure(__filePath);
	}
	return __ins;
}

Configure::Configure() :
		m_threadCnt(0), m_dbSize(0), m_taskSize(0) {

}

Configure::Configure(const char *filePath) {

	FILE *fp = fopen(filePath, "r");
	char buf[512];
	char *ptr;
	std::string str;
	size_t ret;

	ret = fread(buf, sizeof(char), 512, fp);

	if( !feof(fp) ) {
		perror("Read incomplete configure file");
	}else if(ret > 0) {

		ptr = strtok(buf, "\n");
		if (ptr != NULL) {

			parse(ptr);

			while ( NULL != (ptr = strtok( NULL, "\n"))) {

				parse(ptr);
			}
		}

	}else {
		ferror(fp);
	}

	fclose(fp);
}

Configure::Configure(uint32_t threadCnt, uint32_t dbSize, uint32_t taskSize) :
		m_threadCnt(threadCnt), m_dbSize(dbSize), m_taskSize(taskSize) {

}

Configure::~Configure() {
	// TODO Auto-generated destructor stub
}

uint32_t Configure::getThreadCnt() {

	return m_threadCnt;
}

uint32_t Configure::getDbSize() {

	return m_dbSize;
}

uint32_t Configure::getTaskSize() {

	return m_taskSize;
}

void Configure::setThreadCnt(uint32_t threadCnt) {

	m_threadCnt = threadCnt;
}

void Configure::setDbSize(uint32_t dbSize) {

	m_dbSize = dbSize;
}

void Configure::setTaskSize(uint32_t taskSize) {

	m_taskSize = taskSize;
}

void Configure::dump() {

	printf("-ThreadCnt %d\tDBSize %d\tTaskSize %d\r\n", getThreadCnt(),
			getDbSize(), getTaskSize());
}

} /* namespace expdb */

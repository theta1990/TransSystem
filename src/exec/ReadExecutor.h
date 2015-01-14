/*
 * ReadExecutor.h
 *
 *  Created on: Dec 18, 2014
 *      Author: volt
 */

#ifndef READEXECUTOR_H_
#define READEXECUTOR_H_

#include "Executor.h"
namespace expdb {

class ReadExecutor : public Executor {
public:

	ReadExecutor();


	int32_t virtual open();
	int32_t virtual next(const Row *&row);
	int32_t virtual close();

	int32_t virtual reset();

	int32_t setInput(char *str, int64_t len){
		m_str = str;
		m_len = len;
		m_pos = 0;
		return SUCCESS;
	}

	int32_t setDesc(const RowDesc *desc) {

		m_desc = desc;
		return SUCCESS;
	}


	inline ExecType virtual getType(){
		return READ;
	}

	Executor *getChild(){
		return NULL;
	}
private:
	char*		m_str;		//这个字段的内存怎么回收呢？
	int64_t 	m_len;
	int64_t		m_pos;
	const RowDesc 	*m_desc;
	Row			m_curRow[1];
};

} /* namespace expdb */

#endif /* READEXECUTOR_H_ */

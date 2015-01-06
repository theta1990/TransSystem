/*
 * GetExecutor.h
 *
 *  Created on: Dec 24, 2014
 *      Author: volt
 */

#ifndef GETEXECUTOR_H_
#define GETEXECUTOR_H_

#include "Executor.h"

namespace expdb {
/**
 * 根据主键获得一个行信息
 */
class GetExecutor: public expdb::Executor {
public:
	GetExecutor();
	virtual ~GetExecutor();
	virtual int32_t open();
	virtual int32_t next(const Row *&);
	virtual int32_t close();
	virtual int32_t setContext(TaskContext *ctx){

		return SUCCESS;
	}
	virtual int32_t addChild(Executor *child);

	int32_t setTable(RowTable *table){
		m_table = table;
		return SUCCESS;
	}

	inline ExecType virtual getType(){
		return GET;
	}

	Executor *getChild(){
		return m_child;
	}
private:

	const RowTable *m_table;
	Executor	*m_child;
	Row			m_curRow;
};

} /* namespace expdb */

#endif /* GETEXECUTOR_H_ */

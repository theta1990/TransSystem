/*
 * InsertExecutor.h
 *
 *  Created on: Dec 17, 2014
 *      Author: volt
 */

#ifndef INSERTEXECUTOR_H_
#define INSERTEXECUTOR_H_

#include "Executor.h"

namespace expdb {

class InsertExecutor : public Executor {

public:

	InsertExecutor();

	int32_t virtual open();
	int32_t virtual next(const Row *&row);
	int32_t virtual close();

	int32_t setTable(RowTable *table);

	ExecType virtual getType(){

		return INSERT;
	}

	int32_t addChild(Executor *childop);

	Executor * getChild(){
		return m_child;
	}

	virtual void destroy(){

	}
private:

	Executor		*m_child;
	RowTable		*m_table;
};


inline int32_t InsertExecutor::setTable(RowTable *table){

	m_table = table;
	return SUCCESS;
}

inline int32_t InsertExecutor::addChild(Executor* childop) {

	m_child = childop;
	return SUCCESS;
}

} /* namespace expdb */

#endif /* INSERTEXECUTOR_H_ */

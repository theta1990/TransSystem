/*
 * IndexScanExecutor.h
 *
 *  Created on: Jan 13, 2015
 *      Author: volt
 */

#ifndef INDEXSCANEXECUTOR_H_
#define INDEXSCANEXECUTOR_H_
#include "Executor.h"
namespace expdb {

class IndexScanExecutor : public Executor{
public:
	IndexScanExecutor();

	virtual int32_t open();
	virtual int32_t next(const Row *&row);
	virtual int32_t close();

	int32_t setIndexKey(RowKey key){
		m_key = key;
		return SUCCESS;
	}

	int32_t setTable(RowTable *table){
		m_table = table;
		return SUCCESS;
	}

	virtual ExecType getType(){

		return INDEXSCAN;
	}

	virtual Executor * getChild(){
		return NULL;
	}

	virtual ~IndexScanExecutor();

	virtual void destroy(){

	}

private:

	RowKey m_key;		//key
	const RowTable *m_table;
	Row		m_row;
};

} /* namespace expdb */

#endif /* INDEXSCANEXECUTOR_H_ */

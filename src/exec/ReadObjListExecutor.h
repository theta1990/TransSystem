/*
 * ReadObjListExecutor.h
 *
 *  Created on: Jan 13, 2015
 *      Author: volt
 */

#ifndef READOBJLISTEXECUTOR_H_
#define READOBJLISTEXECUTOR_H_

#include <vector>
#include "Executor.h"

namespace expdb {

class ReadObjListExecutor : public Executor{
public:
	ReadObjListExecutor();

	virtual int32_t open();
	virtual int32_t next(const Row *&row);
	virtual int32_t close();

	virtual int32_t reset();

	virtual int32_t setDesc(const RowDesc *);
	virtual int32_t addObjList(RowObj *list, int32_t size);
	virtual int32_t addObjList(std::vector<RowObj> list);
	virtual int32_t addObj(RowObj obj);

	virtual ExecType getType(){

		return READOBJLIST;
	}

	virtual Executor *getChild() {
		return NULL;
	}

	virtual ~ReadObjListExecutor();

private:
	std::vector<RowObj> m_objList;
	const RowDesc *m_desc;
	Row m_curRow[1];
	int64_t	m_pos;
};

} /* namespace expdb */

#endif /* READOBJLISTEXECUTOR_H_ */

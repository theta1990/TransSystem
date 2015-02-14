/*
 * ScanExecutor.h
 *
 *  Created on: Feb 12, 2015
 *      Author: volt
 */

#ifndef SCANEXECUTOR_H_
#define SCANEXECUTOR_H_

#include "Executor.h"

namespace expdb {

class ScanExecutor: public expdb::Executor {
public:
	ScanExecutor(const RowTable *table);
	virtual ~ScanExecutor();

	int32_t virtual open();
	int32_t virtual next(const Row *&row);
	int32_t virtual close();

	ExecType virtual getType() {

		return SCAN;
	}

	virtual Executor *getChild() {

		return NULL;
	}

	void virtual destroy() {

		m_table = NULL;
	}
private:

	const RowTable *		m_table;
	RowTable::TableIterator m_it;
	Row						m_row;

};

} /* namespace expdb */

#endif /* SCANEXECUTOR_H_ */

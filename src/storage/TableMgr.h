/*
 * TableMgr.h
 *
 *  Created on: Jan 9, 2015
 *      Author: volt
 */

#ifndef TABLEMGR_H_
#define TABLEMGR_H_
#include "../common.h"
#include "RowTable.h"
#include <vector>
namespace expdb {


class TableMgr {
public:
	virtual ~TableMgr();

	static TableMgr * getInstance();

	int32_t getTable(int32_t id, RowTable *&);
	int32_t createTable(const RowDesc *desc, int32_t &id);

private:
	TableMgr();

	static TableMgr *ins__;

	std::vector<RowTable *> m_tableList;
	std::vector<int8_t> 	m_flags;
	volatile uint32_t		m_Count;
};

} /* namespace expdb */

#endif /* TABLEMGR_H_ */

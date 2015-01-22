/*
 * SchemaMgr.h
 *
 *  Created on: Dec 19, 2014
 *      Author: volt
 */

#ifndef SCHEMAMGR_H_
#define SCHEMAMGR_H_

#include "RowDesc.h"
#include "../trans/QLock.h"

#define MAXNAMELEN 	256
#define MAXTABLENUM	16
namespace expdb {

struct TableInfo{

	char	m_tableName[MAXNAMELEN];
	int32_t m_tableId;
	RowDesc m_desc;
};


class SchemaMgr {
public:

	static SchemaMgr * getInstance();

	virtual ~SchemaMgr();

	int32_t getTableDesc(const char *name, 		const RowDesc *&desc);
	int32_t getTableDesc(const int32_t tableId, const RowDesc *&desc);
	int32_t getTableId(const char *name, int32_t &tableId);

	int32_t addTable(const char *name, const RowDesc *desc, const RowDesc *&storedDesc);

private:
	SchemaMgr();

	static SchemaMgr * ins__;


	TableInfo	m_tableList[MAXTABLENUM];
	int32_t		m_tableCnt;
	QLock 		m_schemaGuard;
};

} /* namespace expdb */

#endif /* SCHEMAMGR_H_ */

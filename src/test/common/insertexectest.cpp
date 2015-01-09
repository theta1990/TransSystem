/*
 * insertexectest.cpp
 *
 *  Created on: Dec 19, 2014
 *      Author: volt
 */

#include "test.h"
#include "../../storage/Row.h"
#include "../../storage/RowTable.h"
#include "../../storage/SchemaMgr.h"
#include "../../trans/TaskContext.h"
#include "../../exec/InsertExecutor.h"
#include "../../exec/ReadExecutor.h"
#include <vector>
using namespace expdb;

extern int rowGen(Row &row);
int rowStreamGen(char *buf, int64_t size, int64_t &pos,
		std::vector<RowKey> &keys) {

	const RowDesc *desc;

	RowKey key;
	SchemaMgr::getInstance()->getTableDesc("hw", desc);
	Row row(desc);
	int count = 10;
	while (count--) {
		rowGen(row);
		row.getRowKey(key);
		keys.push_back(key);
		if (SUCCESS != row.serilization(buf, size, pos)) {
			break;
		}
	}
	return 0;
}

int insertexectest(int argc, char **argv) {

	RowTable table;
	const RowDesc *desc;
	char buf[1024];
	int64_t pos = 0;

	SchemaMgr::getInstance()->getTableDesc("hw", desc);
	table.setDesc(desc);

	TaskContext ctx;

	Executor *insertExec = new InsertExecutor();

	Allocator alloc;
	std::vector<RowKey> keys;
	rowStreamGen(buf, 1024, pos, keys);
	Executor *exec = new ReadExecutor();

	static_cast<InsertExecutor*>(insertExec)->addChild(exec);

	insertExec->open();
	insertExec->close();
	printf("---------------insert finished------------------");

	Row row(desc);
	for (uint32_t i = 0; i < keys.size(); ++i) {
		table.get(keys[i], row);
		row.dump();
	}

	delete insertExec;
	return 0;
}
//TEST(insertexectest);


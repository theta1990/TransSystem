/*
 * updateexectest.cpp
 *
 *  Created on: Dec 23, 2014
 *      Author: volt
 */
#include "test.h"
#include "../../storage/Row.h"
#include "../../storage/RowTable.h"
#include "../../storage/SchemaMgr.h"
#include "../../trans/TaskContext.h"
#include "../../exec/InsertExecutor.h"
#include "../../exec/ReadExecutor.h"
#include "../../exec/UpdateExecutor.h"
#include "../../exec/Expression.h"
#include <vector>
using namespace expdb;

extern int rowStreamGen(char *buf, int64_t size, int64_t &pos,
		std::vector<RowKey> &keys);

int updateexectest(int argc, char **argv){

	RowTable table;
	const RowDesc *desc;
	char buf[1024];
	int64_t pos = 0;

	SchemaMgr::getInstance()->getTableDesc("hw", desc);
	table.setDesc(desc);

	TaskContext ctx;
	std::vector<RowKey> keys;
	rowStreamGen(buf, 1024, pos, keys);

	Expression exp(1, ASSI);

	RowObj obj;
	obj.setMidInt(1);
	exp.setArg(obj);

	Executor *updateExec = new UpdateExecutor();
	Executor *insertExec = new InsertExecutor();

	Executor *exec = new ReadExecutor();
	static_cast<UpdateExecutor*>(updateExec)->addChild(exec);
	static_cast<InsertExecutor*>(insertExec)->addChild(exec);

	insertExec->open();
	insertExec->close();

	printf("---------------insert finished------------------\n");
	Row row(desc);
	for (uint32_t i = 0; i < keys.size(); ++i) {
		table.get(keys[i], row);
		row.dump();
	}


	static_cast<ReadExecutor*>(exec)->reset();

	updateExec->open();
	updateExec->close();
	//	updateExec->open();
//	updateExec->close();
	printf("---------------update finished------------------\n");

	for (uint32_t i = 0; i < keys.size(); ++i) {
		table.get(keys[i], row);
		row.dump();
	}

	delete updateExec;
	delete insertExec;
	return 0;
}
//TEST(updateexectest);


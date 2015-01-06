/*
 * getexectest.cpp
 *
 *  Created on: Dec 25, 2014
 *      Author: volt
 */

#include "test.h"
#include "../../storage/Row.h"
#include "../../storage/RowTable.h"
#include "../../storage/SchemaMgr.h"
#include "../../trans/TaskContext.h"
#include "../../exec/InsertExecutor.h"
#include "../../exec/ReadExecutor.h"
#include "../../exec/GetExecutor.h"
#include <vector>

using namespace expdb;
extern int rowStreamGen(char *buf, int64_t size, int64_t &pos,
		std::vector<RowKey> &keys);

int getexectest(int argc, char **argv){

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
	printf("---------------insert finished------------------\r\n");


	Executor *getExec = new GetExecutor();
	static_cast<GetExecutor *>(getExec)->addChild(exec);
	static_cast<ReadExecutor *>(exec)->open();

	getExec->open();
	const Row *row;
	while( SUCCESS == getExec->next(row)){
		row->dump();
	}

	return 0;
}
//TEST(getexectest);



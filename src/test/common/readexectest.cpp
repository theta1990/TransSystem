/*
 * exectest.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: volt
 */

#include "test.h"
#include <string.h>
#include "../../storage/Row.h"
#include "../../storage/SchemaMgr.h"
#include "../../exec/Executor.h"
#include "../../exec/ReadExecutor.h"
#include "../../common/memory/Allocator.h"
using namespace expdb;
/**
 * 测试执行算子的效果
 */
int exectest(int argc, char ** argv) {


	const RowDesc *des;
	RowObj obj, obj2;
	char buf[1024];
	int64_t size = 1024;
	int64_t pos = 0;

	obj.setSmallInt(20);
	obj2.setMidInt(40);

	SchemaMgr::getInstance()->getTableDesc("hw", des);
	Row row(des);
	row.setDesc(des);
	row.addCol(obj, 0);
	row.addCol(obj2, 1);

	row.serilization(buf, size, pos);

	const Row *readrow;
	Executor *exec = new ReadExecutor();

	exec->open();

	while (END != exec->next(readrow)) {
		readrow->dump();
		printf("\n");
	}

	exec->close();
	return 0;
}
//TEST(exectest);

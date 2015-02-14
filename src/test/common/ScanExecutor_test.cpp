/*
 * ScanExecutor_test.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: volt
 */

#include "../../exec/ScanExecutor.h"
#include "../../exec/PhyPlanFactory.h"
#include "../../trans/MyServer.h"
#include "../common/test.h"
#include "../../storage/TableMgr.h"
#include "../../storage/SchemaMgr.h"
#include "../../common/serialization.h"
#include "../gen/TestProcedure.h"
using namespace expdb;

extern void load();
int scanExecutorTest(int argc, char **argv) {

	RowTable *table;
	const Row	*row;

	int32_t i = 0;
	MyServer server(Configure::getInstance());
	RowObj* objList;
	load();
	server.startServer();

	for (i = 0; i < RECORDSIZE; ++i) {

		objList = (RowObj*)malloc(sizeof(RowObj) * 2);
		objList[0] = RowObj(static_cast<uint32_t>(i));	//这里会不会有问题，objList[0] 实例直接采用赋值产生？连初始化都没有
		objList[1] = RowObj(static_cast<uint32_t>(1000));

		server.handleTask(StoredProcedureTask(AddProcedure::getInstance(), objList, 2));
	}


	int32_t tableId;
	SchemaMgr::getInstance()->getTableId("hppaper", tableId);
	TableMgr::getInstance()->getTable(tableId, table);

	ScanExecutor exec(table);

	exec.open();

	int count = 0;
	while( END != exec.next(row) ) {

		row->dump();
		++count;
//		printf("\n");
	}
	printf("%d\n", count);

	exec.close();
	return 0;
}
TEST(scanExecutorTest);


/*
 * hpmicrosoft.cpp
 *
 *  Created on: Feb 3, 2015
 *      Author: volt
 */
#include "../../exec/PhyPlanFactory.h"
#include "../../trans/MyServer.h"
#include "../common/test.h"
#include "../../storage/TableMgr.h"
#include "../../storage/SchemaMgr.h"
#include "../../common/serialization.h"
using namespace expdb;

#define READTIMES 6
#define WRITETIEMS 6
#define RECORDSIZE 1000000
/**
 * Account: name, money
 */
void load() {

	RowDesc desc;
	const RowDesc *storedDesc;
	int32_t id;
	desc.addRowType(MIDINT);
	desc.addRowType(MIDINT);
	int32_t priIdx[8];

	priIdx[0] = 0;
	desc.setPriIdx(priIdx, 1);

	if (SUCCESS
			!= SchemaMgr::getInstance()->addTable("hppaper", &desc,
					storedDesc)) {

		VOLT_ERROR("Create schema failed");
	} else if (TableMgr::getInstance()->createTable(storedDesc, id)
			!= SUCCESS) {

		VOLT_ERROR("Create table failed");
	}
}

int32_t genAddtask(TransTask &task, RowObj *objList, uint32_t size) {

	PhyPlan *plan;
	RowTable *table;
	int32_t tableId;
	SchemaMgr::getInstance()->getTableId("hppaper", tableId);
	TableMgr::getInstance()->getTable(tableId, table);

	assert(size == 2);

	std::vector<RowObj> list;
	list.push_back(objList[0]);
	list.push_back(objList[1]);

	if (SUCCESS
			== PhyPlanFactory::getInstance()->genInsertPlan(plan, list,
					table)) {
		task.addPhyPlan(plan);
		return SUCCESS;
	} else {
		VOLT_ERROR("Create plan failed");
		return ERROR;
	}
}



int32_t genTransactionTask(TransTask &task, RowObj *objList, uint32_t size) {

	//a reads, b writes;
	PhyPlan *plan;
	RowTable *table;
	int32_t tableId;
	SchemaMgr::getInstance()->getTableId("hppaper", tableId);
	TableMgr::getInstance()->getTable(tableId, table);

	Expression expr1(1, MIN), expr2(1, ADD);

//	std::vector<RowObj>::iterator it = objList.begin();
	RowObj *it = objList;
	RowObj *end = objList + size;
	expr1.setArg(*it++);
	expr2.setArg(*it++);
	for (int i = 0; i < READTIMES && it != end; ++i) {

		RowKey key;
		key.addKey(*it++);
		if (SUCCESS
				== PhyPlanFactory::getInstance()->genUpdatePlan(plan, key,
						expr1, table)) {
			task.addPhyPlan(plan);
		}
	}

	for (int i = 0; i < WRITETIEMS  && it != end; ++i) {
		RowKey key;
		key.addKey(*it++);
		if (SUCCESS
				== PhyPlanFactory::getInstance()->genUpdatePlan(plan, key,
						expr2, table)) {
			task.addPhyPlan(plan);
		}
	}

	return SUCCESS;
}

void genTransactionParameter(RowObj* &list, uint32_t &size){

	uint32_t idx = 0;
	size = READTIMES + WRITETIEMS + 2;
	list = (RowObj *)malloc(sizeof(RowObj) * size);
//	list.push_back(RowObj(static_cast<uint32_t>(1)));
//	list.push_back(RowObj(static_cast<uint32_t>(1)));
	list[idx++] = RowObj(static_cast<uint32_t>(1));
	list[idx++] = RowObj(static_cast<uint32_t>(1));

	uint32_t seed = rand() % RECORDSIZE;

	for (int i = 0; i < READTIMES; ++i) {

		list[idx++] = RowObj((seed++) % RECORDSIZE);
	}

	for (int i = 0; i < WRITETIEMS; ++i) {

		list[idx++] = RowObj((seed++) % RECORDSIZE);
	}
}


int hpCCTest(int argc, char **argv) {

	int32_t i = 0;
	uint32_t size;
	MyServer server;
	int32_t taskCount = 1000000;
	load();
	server.startServer();

//	std::vector<RowObj> objList;
	RowObj* objList;
	for (i = 0; i < RECORDSIZE; ++i) {
//		objList.clear();
//		objList.push_back(RowObj(static_cast<uint32_t>(i)));
//		objList.push_back(RowObj(static_cast<uint32_t>(1000)));

		objList = (RowObj*)malloc(sizeof(RowObj) * 2);
		objList[0] = RowObj(static_cast<uint32_t>(i));
		objList[1] = RowObj(static_cast<uint32_t>(1000));
		server.handleTask(RawTask(genAddtask, objList, 2));
	}
	//	task.destroy();
	printf("-Load data finished\n");
	sleep(10);

	long startTimeStamp = common::getTimeOfMs();
	for (i = 0; i < taskCount; ++i) {
		genTransactionParameter(objList, size);
		server.handleTask(RawTask(genTransactionTask, objList, size));
	}
	server.exit();
	server.waitForExit();
	long endTimeStamp = common::getTimeOfMs();

	printf("-TPS: %ld\n", taskCount / ((endTimeStamp-startTimeStamp) / 1000000));

	return 0;
}
//TEST(hpCCTest);


int hpCCSpTest(int arc, char **argv) {


	int32_t i = 0;
	uint32_t size;
	MyServer server;
	int32_t taskCount = 1000000;
	RowObj* objList;
	for (i = 0; i < RECORDSIZE; ++i) {

		objList = (RowObj*)malloc(sizeof(RowObj) * 2);
		objList[0] = RowObj(static_cast<uint32_t>(i));
		objList[1] = RowObj(static_cast<uint32_t>(1000));

		server.handleTask(StoredProcedureTask(AddProcedure::getInstance(), objList, 2));
	}

	printf("-Load data finished\n");
	sleep(10);

	long startTimeStamp = common::getTimeOfMs();
	for (i = 0; i < taskCount; ++i) {
		genTransactionParameter(objList, size);
		server.handleTask(StoredProcedureTask(TransferTask::getIntance(), objList, size));
	}
	server.exit();
	server.waitForExit();
	long endTimeStamp = common::getTimeOfMs();

	printf("-TPS: %ld\n", taskCount / ((endTimeStamp-startTimeStamp) / 1000000));


}


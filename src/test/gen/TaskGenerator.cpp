#include "../../exec/PhyPlanFactory.h"
#include "../../trans/MyServer.h"
#include "../common/test.h"
#include "../../storage/TableMgr.h"
#include "../../storage/SchemaMgr.h"
#include "../../common/serialization.h"
using namespace expdb;

/**
 * Account: name, money
 */
void createAccountTable() {

	RowDesc desc;
	int32_t id;
	desc.addRowType(SMALLINT);
	desc.addRowType(MIDINT);
	int32_t priIdx[8];

	priIdx[0] = 0;
	desc.setPriIdx(priIdx, 1);

	if (SUCCESS != SchemaMgr::getInstance()->addTable("account", &desc)) {

		VOLT_ERROR("Create schema failed");
	} else if (TableMgr::getInstance()->createTable(&desc, id) != SUCCESS) {

		VOLT_ERROR("Create table failed");
	}
}

/**
 * Account: name1, name2, money
 */
void createRecordTable() {

	RowDesc desc;
	int32_t id;

	desc.addRowType(SMALLINT);
	desc.addRowType(SMALLINT);
	desc.addRowType(MIDINT);

	if (SUCCESS != SchemaMgr::getInstance()->addTable("record", &desc)) {

		VOLT_ERROR("Create schema failed");
	} else if (TableMgr::getInstance()->createTable(&desc, id) != SUCCESS) {

		VOLT_ERROR("Create table failed");
	}
}

int32_t genAccountStringFormat(uint16_t id, uint32_t money, char *inputString,
		const int sz, int64_t &pos) {

	int32_t ret = SUCCESS;
	if (SUCCESS != encode_i16(inputString, sz, pos, id)) {

		ret = ERROR;
	} else if (SUCCESS != encode_i32(inputString, sz, pos, id)) {

		ret = ERROR;
	}
	return ret;
}

void genAddAccountTask(TransTask &task, char *inputValues, int32_t sz) {

	PhyPlan *plan;
	RowTable *table;
	TableMgr::getInstance()->getTable(0, table);

	PhyPlanFactory::getInstance()->genInsertPlan(plan, inputValues, sz, table);
	task.addPhyPlan(plan);
}

void genAddAccouttask(TransTask &task, uint16_t id, uint32_t money){

	PhyPlan *plan;
	RowTable *table;
	TableMgr::getInstance()->getTable(0, table);

	std::vector<RowObj> objList;
	objList.push_back(RowObj(id));
	objList.push_back(RowObj(money));
	PhyPlanFactory::getInstance()->genInsertPlan(plan, objList,table);
	task.addPhyPlan(plan);
}


void genTransferTask(TransTask &task, uint16_t id1, uint16_t id2, uint32_t money) {

	PhyPlan *sourcePlan, *destPlan, *recordPlan;
	RowTable *account, *record;

	TableMgr::getInstance()->getTable(0, account);
	TableMgr::getInstance()->getTable(1, record);

	Expression expr1(1, MIN);
	RowObj obj1;
	RowKey key1;
	obj1.setMidInt(money);
	expr1.setArg(obj1);

	obj1.setSmallInt(id1);
	PhyPlanFactory::getInstance()->genUpdatePlan(sourcePlan, key1, expr1,
			account);


	RowObj obj2;
	RowKey key2;
	Expression expr2(1, ADD);
	obj2.setMidInt(money);
	expr2.setArg(obj2);

	obj2.setSmallInt(id2);
	PhyPlanFactory::getInstance()->genUpdatePlan(destPlan, key2, expr2, account);


	std::vector<RowObj> objList;
	objList.push_back(RowObj(id1));
	objList.push_back(RowObj(id2));
	objList.push_back(RowObj(money));
	PhyPlanFactory::getInstance()->genInsertPlan(recordPlan, objList, record);

	task.addPhyPlan(sourcePlan);
	task.addPhyPlan(destPlan);
	task.addPhyPlan(recordPlan);
}


int startGenerator(int argc, char **argv) {

	int32_t i = 0;

	createAccountTable();
	createRecordTable();

	TransTask task;
	int32_t count;
//	MyServer server;
//	server.startServer();

	for(i=0;i<1000000;+i){
		task.destroy();
		task.setTranId(count++);
		genAddAccouttask(task, i, 1000);
//		server.handleTask(task);
	}
	task.destroy();

//	for(i=0;i<10000000;++i){
//		task.destroy();
//		task.setTranId(count++);
//		genTransferTask(task, rand()%10000, rand()%10000, rand()%10);
//	}
	task.destroy();

	return 0;
}
//TEST(startGenerator);


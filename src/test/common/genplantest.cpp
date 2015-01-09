#include "test.h"
#include "../../storage/SchemaMgr.h"
#include "../../trans/TaskContext.h"

#include "../../exec/Executor.h"
#include "../../exec/PhyPlan.h"
#include "../../exec/PhyPlanFactory.h"

using namespace expdb;
extern int rowGen(Row &row);
extern int rowStreamGen(char *buf, int64_t size, int64_t &pos,
		std::vector<RowKey> &keys);
int genPlanTest(int argc, char **argv) {

	RowTable table;
	const RowDesc *desc;
	PhyPlan *plan = NULL;

	Allocator alloc;
	TaskContext *ctx;

	std::vector<RowKey> keys;
	int64_t pos = 0;
	char buf[10240];

	rowStreamGen(buf, 10240, pos, keys);
	alloc.init(0);

	SchemaMgr::getInstance()->getTableDesc("hw", desc);
	table.setDesc(desc);

	TaskContextMgr::getInstance()->newContext(1, ctx, alloc);

	PhyPlanFactory::getInstance()->genInsertPlan(plan, buf, pos, &table);

	plan->setContext(ctx);
	plan->getQuery()->open();
	plan->getQuery()->close();

	printf("------------insert finished--------------\r\n");

	Row row(desc);
	for (uint32_t i = 0; i < keys.size(); ++i) {
		if (table.get(keys[i], row) == SUCCESS)
			row.dump();
	}
	ctx->postProcess();

	TaskContextMgr::getInstance()->releaseContext(ctx, alloc);
	ctx = NULL;

//	printf("--------------------------------------------\r\n");
//	printf("-------------update test--------------------\r\n");
//
//	Expression expr(1, ADD);
//	RowObj arg;
//	arg.setMidInt(10);
//	expr.setArg(arg);
//
//	TaskContextMgr::getInstance()->newContext(2, ctx, alloc);
//	PhyPlanFactory::getInstance()->genUpdatePlan(plan, buf, pos, &expr, &table);
//
//	plan->setContext(ctx);
//	plan->getQuery()->open();
//	plan->getQuery()->close();
//
//	ctx->postProcess();
//	for (uint32_t i = 0; i < keys.size(); ++i) {
//		table.get(keys[i], row);
//		row.dump();
//	}
//	TaskContextMgr::getInstance()->releaseContext(ctx, alloc);
//
//	printf("-----------------------------------------\r\n");
//	printf("-------------get test--------------------\r\n");
//
//	PhyPlanFactory::getInstance()->genSelectPlan(plan, buf, pos, &table);
//	plan->getQuery()->open();
//
//	const Row *rowPtr;
//	while (plan->getQuery()->next(rowPtr) != END) {
//		rowPtr->dump();
//	}

	return 0;
}
TEST(genPlanTest);


/*
 * TestProcedure.h
 *
 *  Created on: Feb 6, 2015
 *      Author: volt
 */

#ifndef TESTPROCEDURE_H_
#define TESTPROCEDURE_H_
#include <assert.h>
#include <stdlib.h>
#include "../../trans/StoredProcedure.h"
#include "../../exec/PhyPlanFactory.h"
#include "../../storage/TableMgr.h"
#include "../../storage/SchemaMgr.h"
#include "../../common/serialization.h"

namespace expdb {
#define READTIMES 6
#define WRITETIEMS 6
#define RECORDSIZE 1000000

class AddProcedure : public StoredProcedure {
public:
	AddProcedure();

	virtual int32_t run(RowObj *objList, uint32_t size,
			TaskContext *ctx) {
		int32_t ret = SUCCESS;

		PhyPlan *plan;
		RowTable *table;
		int32_t tableId;
		ResultSet *results;
		SchemaMgr::getInstance()->getTableId("hppaper", tableId);
		TableMgr::getInstance()->getTable(tableId, table);

		assert(size == 2);

		std::vector<RowObj> list;
		list.push_back(objList[0]);
		list.push_back(objList[1]);

		if (SUCCESS
				== PhyPlanFactory::getInstance()->genInsertPlan(plan, list,
						table)) {
			ret = executePhyPlan(*plan, ctx, results);
		}

		PhyPlanFactory::getInstance()->deletePlan(plan);

		if (END == ret)
			ret = SUCCESS;
		return ret;
	}

	static StoredProcedure* getInstance();

private:
	static StoredProcedure *_ins;
};

class TransferTask : public StoredProcedure {
public:
	TransferTask();

	virtual int32_t run(RowObj *objList, uint32_t size, TaskContext *ctx){
		int32_t ret = SUCCESS;

		PhyPlan *plan;
		RowTable *table;
		int32_t tableId;
		ResultSet *results;
		SchemaMgr::getInstance()->getTableId("hppaper", tableId);
		TableMgr::getInstance()->getTable(tableId, table);

		Expression expr1(1, MIN), expr2(1, ADD);

	//	std::vector<RowObj>::iterator it = objList.begin();
		RowObj *it = objList;
		RowObj *end = objList + size;
		expr1.setArg(*it++);
		expr2.setArg(*it++);
		for (int i = 0; i < READTIMES && it != end && SUCCESS == ret ; ++i) {

			RowKey key;
			key.addKey(*it++);
			if (SUCCESS
					== (ret = PhyPlanFactory::getInstance()->genUpdatePlan(plan,
							key, expr1, table))) {
				ret = executePhyPlan(*plan, ctx, results);
				PhyPlanFactory::getInstance()->deletePlan(plan);
			}
		}

		for (int i = 0; i < WRITETIEMS && it != end && SUCCESS == ret; ++i) {
			RowKey key;
			key.addKey(*it++);
			if (SUCCESS
					== (ret = PhyPlanFactory::getInstance()->genUpdatePlan(plan,
							key, expr2, table))) {
				ret = executePhyPlan(*plan, ctx, results);
				PhyPlanFactory::getInstance()->deletePlan(plan);
			}
		}

		return ret;
	}

	static StoredProcedure* getInstance() ;

private:
	static StoredProcedure *_ins;
};


} /* namespace expdb */

#endif /* TESTPROCEDURE_H_ */

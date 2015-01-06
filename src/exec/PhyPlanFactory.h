/*
 * PhyPlanFactory.h
 *
 *  Created on: Dec 25, 2014
 *      Author: volt
 */

#ifndef PHYPLANFACTORY_H_
#define PHYPLANFACTORY_H_

#include "PhyPlan.h"
#include "Expression.h"
#include "../common/memory/Allocator.h"
#include "../storage/RowTable.h"
#include "Expression.h"
namespace expdb {

/**
 * 生成某种类型sql的物理计划
 */
class PhyPlanFactory {
public:

	static PhyPlanFactory *getInstance();
	int32_t deletePlan(PhyPlan *&plan);	//TODO

	virtual ~PhyPlanFactory();

	int32_t genInsertPlan(PhyPlan *&plan, char *inputValues, int32_t sz, RowTable *table);
	int32_t genSelectPlan(PhyPlan *&plan, char *inputVaules, int32_t sz, RowTable *table);
	int32_t genUpdatePlan(PhyPlan *&plan, char *inputValues, int32_t sz ,Expression *expr, RowTable *table);	//逻辑计划上的update内部应该是会包含这些参数信息的
	int32_t genDeletePlan();

private:
	PhyPlanFactory();
	static PhyPlanFactory *ins_;
	Allocator m_alloc;
};

} /* namespace expdb */

#endif /* PHYPLANFACTORY_H_ */

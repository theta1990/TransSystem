/*
 * PhyPlan.h
 *
 *  Created on: Dec 25, 2014
 *      Author: volt
 */

#ifndef PHYPLAN_H_
#define PHYPLAN_H_

#include "../common.h"
#include <vector>
namespace expdb {

class PhyPlanFactory;

enum PhyPlanType{
	PhyInsert,
	PhyUpdate,
	PhyRead,
	PhyDelete
};

/**
 * 描述一种sql语句的物理算子
 * support for curd
 * create, insert statement
 * update statement
 * read statement
 * delete statement
 */
class TaskContext;
class Executor;
class PhyPlan {
	friend class PhyPlanFactory;
public:
	PhyPlan();

	int32_t setContext(TaskContext *ctx){

		m_ctx = ctx;
		return SUCCESS;
	}

	Executor *getQuery(){

		return m_query;
	}

	TaskContext *getTaskContext(){

		return m_ctx;
	}

	void destory();

	virtual ~PhyPlan();

private:
	Executor *m_query;
	TaskContext	*m_ctx;
};

} /* namespace expdb */

#endif /* PHYPLAN_H_ */

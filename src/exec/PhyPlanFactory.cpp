/*
 * PhyPlanFactory.cpp
 *
 *  Created on: Dec 25, 2014
 *      Author: volt
 */

#include "PhyPlanFactory.h"
#include "ReadExecutor.h"
#include "InsertExecutor.h"
#include "UpdateExecutor.h"
#include "GetExecutor.h"
#include "../storage/TableMgr.h"
namespace expdb {

PhyPlanFactory * PhyPlanFactory::ins_ = NULL;

PhyPlanFactory * PhyPlanFactory::getInstance() {

	if ( NULL == ins_) {

		ins_ = new PhyPlanFactory();
		ins_->m_alloc.init(0);
	}
	return ins_;
}

PhyPlanFactory::PhyPlanFactory() {
	// TODO Auto-generated constructor stub

}

PhyPlanFactory::~PhyPlanFactory() {
	// TODO Auto-generated destructor stub
}

int32_t PhyPlanFactory::deletePlan(PhyPlan*& plan) {

	Executor *exec = plan->m_query;
	Executor *nxt = NULL;
	while (NULL != exec) {
		nxt = exec->getChild();
		m_alloc.free(exec);
		exec = nxt;
	}
	m_alloc.free(plan);
	plan = NULL;
	return SUCCESS;
}

int32_t PhyPlanFactory::genInsertPlan(PhyPlan *&plan, char *inputValues,
		int32_t sz, RowTable* table) {

	int32_t ret = SUCCESS;

	void *p = m_alloc.alloc(sizeof(ReadExecutor));
	ReadExecutor *readExec = new (p) ReadExecutor();
	const RowDesc *desc;
	table->getDesc(desc);
	readExec->setDesc(desc);
	readExec->setInput(inputValues, sz);

	p = m_alloc.alloc(sizeof(InsertExecutor));
	InsertExecutor *insertExec = new (p) InsertExecutor();

	insertExec->setTable(table);
	insertExec->addChild(readExec);

	p = m_alloc.alloc(sizeof(PhyPlan));
	plan = new (p) PhyPlan();
	plan->m_query = insertExec;

	readExec->setPhyPlan(plan);
	insertExec->setPhyPlan(plan);

	return ret;
}

int32_t PhyPlanFactory::genSelectPlan(PhyPlan *&plan, char *inputValues,
		int32_t sz, RowTable *table) {

	int32_t ret = SUCCESS;

	void *p = m_alloc.alloc(sizeof(GetExecutor));
	GetExecutor *getExec = new (p) GetExecutor();

	p = m_alloc.alloc(sizeof(ReadExecutor));
	ReadExecutor *readExec = new (p) ReadExecutor();

	getExec->setTable(table);
	getExec->addChild(readExec);

	const RowDesc *desc;
	if (SUCCESS != (ret = table->getDesc(desc))) {

		VOLT_ERROR("get row description fail");
	} else {

		readExec->setDesc(desc);
		readExec->setInput(inputValues, sz);
		p = m_alloc.alloc(sizeof(PhyPlan));
		plan = new (p) PhyPlan();
		plan->m_query = getExec;

		getExec->setPhyPlan(plan);
		readExec->setPhyPlan(plan);
	}
	return ret;
}

/**
 * 生成update的物理计划，最好能让read op只读取RowKey 信息
 */
int32_t PhyPlanFactory::genUpdatePlan(PhyPlan *&plan, char *inputValues,
		int32_t sz, Expression expr, RowTable *table) {

	int32_t ret = SUCCESS;

	void *p = m_alloc.alloc(sizeof(UpdateExecutor));

	UpdateExecutor *updateExec = new (p) UpdateExecutor();
	updateExec->setExpr(expr);
	updateExec->setTable(table);

	p = m_alloc.alloc(sizeof(ReadExecutor));
	ReadExecutor *readExec = new (p) ReadExecutor();
	const RowDesc *desc;
	if (SUCCESS != (ret = table->getDesc(desc))) {
		VOLT_ERROR("get table description fail");
	} else {
		readExec->setDesc(desc);
		readExec->setInput(inputValues, sz);
		updateExec->addChild(readExec);

		p = m_alloc.alloc(sizeof(plan));
		plan = new (p) PhyPlan();
		plan->m_query = updateExec;

		updateExec->setPhyPlan(plan);
		readExec->setPhyPlan(plan);
	}
	return ret;
}

int32_t PhyPlanFactory::genUpdatePlan(PhyPlan *&plan, RowKey key,
		Expression expr, RowTable * table) {

	int32_t ret = SUCCESS;

	void *p = m_alloc.alloc(sizeof(UpdateExecutor));

	UpdateExecutor *updateExec = new (p) UpdateExecutor();
	updateExec->setExpr(expr);
	updateExec->setTable(table);

	p = m_alloc.alloc(sizeof(IndexScanExecutor));
	IndexScanExecutor *indexExec = new (p) IndexScanExecutor();
	const RowDesc *desc;
	if (SUCCESS != (ret = table->getDesc(desc))) {
		VOLT_ERROR("get table description fail");
	} else {
		indexExec->setIndexKey(key);
		indexExec->setTable(table);
		updateExec->addChild(indexExec);

		p = m_alloc.alloc(sizeof(plan));
		plan = new (p) PhyPlan();
		plan->m_query = updateExec;

		updateExec->setPhyPlan(plan);
		indexExec->setPhyPlan(plan);
	}
	return ret;
}

int32_t PhyPlanFactory::genInsertPlan(PhyPlan*& plan, char* inputValues,
		int32_t sz, int32_t tableId) {

	RowTable *table = NULL;
	if( TableMgr::getInstance()->getTable(tableId, table) == SUCCESS ) {
		genInsertPlan(plan, inputValues, sz, table);
		return SUCCESS;
	}else return ERROR;
}

int32_t PhyPlanFactory::genSelectPlan(PhyPlan*& plan, char* inputVaules,
		int32_t sz, int32_t tableId) {

	RowTable *table = NULL;
	if( TableMgr::getInstance()->getTable(tableId, table) == SUCCESS ){
		genSelectPlan(plan, inputVaules, sz, table);
		return SUCCESS;
	}else return ERROR;
}

int32_t PhyPlanFactory::genUpdatePlan(PhyPlan*& plan, char* inputValues,
		int32_t sz, Expression expr, int32_t tableId) {

	RowTable *table = NULL;
	if( TableMgr::getInstance()->getTable(tableId, table) == SUCCESS ){
		genUpdatePlan(plan, inputValues, sz, expr, table);
		return SUCCESS;
	}else return ERROR;
}

int32_t PhyPlanFactory::genUpdatePlan(PhyPlan *&plan, RowKey key,
		Expression expr, int32_t tableId) {

	RowTable *table = NULL;
	if( TableMgr::getInstance()->getTable(tableId, table) == SUCCESS ){
		genUpdatePlan(plan, key, expr, table);
		return SUCCESS;
	}else return ERROR;
}

int32_t PhyPlanFactory::genDeletePlan() {

	VOLT_DEBUG("not supported now");
	return ERROR;
}

} /* namespace expdb */


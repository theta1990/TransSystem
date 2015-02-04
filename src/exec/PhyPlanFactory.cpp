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
#include "IndexScanExecutor.h"
#include "ReadObjListExecutor.h"
#include "../storage/TableMgr.h"
namespace expdb {

PhyPlanFactory * PhyPlanFactory::ins_ = NULL;

PhyPlanFactory * PhyPlanFactory::getInstance() {

	if ( NULL == ins_) {

		ins_ = new PhyPlanFactory();
	}
	return ins_;
}

PhyPlanFactory::PhyPlanFactory() : m_alloc() {
	// TODO Auto-generated constructor stub

}

PhyPlanFactory::~PhyPlanFactory() {
	// TODO Auto-generated destructor stub
}

int32_t PhyPlanFactory::deletePlan(PhyPlan*& plan) {

	plan->destory(m_alloc);
	m_alloc.free(plan);
	plan = NULL;
	return SUCCESS;
}

int32_t PhyPlanFactory::genInsertPlan(PhyPlan *&plan, char *inputValues,
		int32_t sz, RowTable* table) {

	int32_t ret = SUCCESS;

	ReadExecutor *readExec;
	InsertExecutor *insertExec;
	const RowDesc *desc;
	void *p = m_alloc.alloc(sizeof(ReadExecutor));
	if ( NULL == p) {
		VOLT_WARN("Memory is not enough");
		ret = ERROR;
	} else {

		readExec = new (p) ReadExecutor();
		table->getDesc(desc);
		readExec->setDesc(desc);
		readExec->setInput(inputValues, sz);
	}

	if (SUCCESS == ret) {
		p = m_alloc.alloc(sizeof(InsertExecutor));

		if ( NULL == p) {
			VOLT_WARN("Memory is not engouth");
			ret = ERROR;
		} else {
			insertExec = new (p) InsertExecutor();
			insertExec->setTable(table);
			insertExec->addChild(readExec);
		}
	}

	if (SUCCESS == ret) {
		p = m_alloc.alloc(sizeof(PhyPlan));

		if ( NULL == p) {
			VOLT_WARN("Memory is not enough");
			ret = ERROR;
		} else {
			plan = new (p) PhyPlan();
			plan->m_query = insertExec;

			readExec->setPhyPlan(plan);
			insertExec->setPhyPlan(plan);
		}
	}
	return ret;
}

int32_t PhyPlanFactory::genInsertPlan(PhyPlan *&plan,
		std::vector<RowObj> &objList, RowTable *table) {

	int32_t ret = SUCCESS;

	ReadObjListExecutor *readObjListExecutor;
	InsertExecutor *insertExec;
	const RowDesc *desc;
	void *p = m_alloc.alloc(sizeof(ReadObjListExecutor));

	if ( NULL == p) {
		VOLT_WARN("Memory is not enough");
		ret = ERROR;
	} else {

		readObjListExecutor = new (p) ReadObjListExecutor();
		table->getDesc(desc);
		readObjListExecutor->setDesc(desc);
		readObjListExecutor->addObjList(objList);
	}

	if (SUCCESS == ret) {
		p = m_alloc.alloc(sizeof(InsertExecutor));

		if ( NULL == p) {
			VOLT_WARN("Memory is not enough");
			ret = ERROR;
		} else {
			insertExec = new (p) InsertExecutor();
			insertExec->setTable(table);
			insertExec->addChild(readObjListExecutor);
		}
	}

	if (SUCCESS == ret) {
		p = m_alloc.alloc(sizeof(PhyPlan));

		if ( NULL == p) {
			VOLT_WARN("Memory is not enough");
			ret = ERROR;
		} else {
			plan = new (p) PhyPlan();
			plan->m_query = insertExec;
			readObjListExecutor->setPhyPlan(plan);
			insertExec->setPhyPlan(plan);
		}
	}
	return ret;
}

int32_t PhyPlanFactory::genSelectPlan(PhyPlan *&plan, char *inputValues,
		int32_t sz, RowTable *table) {

	int32_t ret = SUCCESS;

	GetExecutor *getExec;
	ReadExecutor *readExec;
	const RowDesc *desc;

	void *p = m_alloc.alloc(sizeof(GetExecutor));

	if ( NULL == p) {
		VOLT_WARN("Memory is not enough");
		ret = ERROR;
	} else {
		readExec = new (p) ReadExecutor();
		table->getDesc(desc);
		readExec->setDesc(desc);
		readExec->setInput(inputValues, sz);
	}

	if (SUCCESS == ret) {
		p = m_alloc.alloc(sizeof(ReadExecutor));
		if ( NULL == p) {
			VOLT_WARN("Memory is not enough");
			ret = ERROR;
		} else {
			getExec = new (p) GetExecutor();
			getExec->setTable(table);
			getExec->addChild(readExec);
		}
	}

	if (SUCCESS == ret) {
		p = m_alloc.alloc(sizeof(PhyPlan));
		if ( NULL == p) {
			VOLT_WARN("Memory is not enough");
			ret = ERROR;
		} else {
			plan = new (p) PhyPlan();
			plan->m_query = getExec;

			getExec->setPhyPlan(plan);
			readExec->setPhyPlan(plan);
		}
	}
	return ret;
}

/**
 * 生成update的物理计划，最好能让read op只读取RowKey 信息
 */
int32_t PhyPlanFactory::genUpdatePlan(PhyPlan *&plan, char *inputValues,
		int32_t sz, Expression& expr, RowTable *table) {

	int32_t ret = SUCCESS;
	UpdateExecutor *updateExec;
	ReadExecutor *readExec;
	const RowDesc *desc;
	void *p = m_alloc.alloc(sizeof(ReadExecutor));
	if ( NULL == p) {
		VOLT_WARN("Memory is not enough");
		ret = ERROR;
	} else {

		readExec = new (p) ReadExecutor();
		table->getDesc(desc);
		readExec->setDesc(desc);
		readExec->setInput(inputValues, sz);
	}

	if (SUCCESS == ret) {
		p = m_alloc.alloc(sizeof(UpdateExecutor));
		if ( NULL == p) {
			VOLT_WARN("Memory is not enough");
			ret = ERROR;
		} else {
			updateExec = new (p) UpdateExecutor();
			updateExec->setExpr(expr);
			updateExec->setTable(table);
			updateExec->addChild(readExec);
		}
	}

	if (SUCCESS == ret) {
		p = m_alloc.alloc(sizeof(plan));

		if ( NULL == p) {
			VOLT_WARN("Memory is not enough");
			ret = ERROR;
		} else {
			plan = new (p) PhyPlan();
			plan->m_query = updateExec;

			updateExec->setPhyPlan(plan);
			readExec->setPhyPlan(plan);
		}
	}
	return ret;
}

int32_t PhyPlanFactory::genUpdatePlan(PhyPlan *&plan, RowKey key,
		Expression& expr, RowTable * table) {

	int32_t ret = SUCCESS;
	UpdateExecutor *updateExec;
	IndexScanExecutor *indexExec;
	const RowDesc *desc;
	void *p;

	p = m_alloc.alloc(sizeof(IndexScanExecutor));
	if ( NULL == p) {
		VOLT_WARN("Memory is not enough");
		ret = ERROR;
	} else {
		indexExec = new (p) IndexScanExecutor();
		table->getDesc(desc);
		indexExec->setIndexKey(key);
		indexExec->setTable(table);
	}

	if (SUCCESS == ret) {
		p = m_alloc.alloc(sizeof(UpdateExecutor));
		if ( NULL == p) {
			VOLT_WARN("Memory is not enough");
			ret = ERROR;
		} else {
			updateExec = new (p) UpdateExecutor();
			updateExec->setExpr(expr);
			updateExec->setTable(table);
			updateExec->addChild(indexExec);
		}
	}

	if (SUCCESS == ret) {
		p = m_alloc.alloc(sizeof(plan));

		if ( NULL == p) {
			VOLT_WARN("Memory is not enough");
			ret = ERROR;
		} else {
			plan = new (p) PhyPlan();
			plan->m_query = updateExec;

			updateExec->setPhyPlan(plan);
			indexExec->setPhyPlan(plan);
		}
	}
	return ret;
}

int32_t PhyPlanFactory::genInsertPlan(PhyPlan*& plan, char* inputValues,
		int32_t sz, int32_t tableId) {

	RowTable *table = NULL;
	if (TableMgr::getInstance()->getTable(tableId, table) == SUCCESS) {
		genInsertPlan(plan, inputValues, sz, table);
		return SUCCESS;
	} else
		return ERROR;
}

int32_t PhyPlanFactory::genInsertPlan(PhyPlan*& plan,
		std::vector<RowObj> &objList, int32_t tableId) {

	RowTable *table = NULL;
	if (TableMgr::getInstance()->getTable(tableId, table) == SUCCESS) {
		genInsertPlan(plan, objList, table);
		return SUCCESS;
	} else
		return ERROR;
}

int32_t PhyPlanFactory::genSelectPlan(PhyPlan*& plan, char* inputVaules,
		int32_t sz, int32_t tableId) {

	RowTable *table = NULL;
	if (TableMgr::getInstance()->getTable(tableId, table) == SUCCESS) {
		genSelectPlan(plan, inputVaules, sz, table);
		return SUCCESS;
	} else
		return ERROR;
}

int32_t PhyPlanFactory::genUpdatePlan(PhyPlan*& plan, char* inputValues,
		int32_t sz, Expression& expr, int32_t tableId) {

	RowTable *table = NULL;
	if (TableMgr::getInstance()->getTable(tableId, table) == SUCCESS) {
		genUpdatePlan(plan, inputValues, sz, expr, table);
		return SUCCESS;
	} else
		return ERROR;
}

int32_t PhyPlanFactory::genUpdatePlan(PhyPlan *&plan, RowKey key,
		Expression& expr, int32_t tableId) {

	RowTable *table = NULL;
	if (TableMgr::getInstance()->getTable(tableId, table) == SUCCESS) {
		genUpdatePlan(plan, key, expr, table);
		return SUCCESS;
	} else
		return ERROR;
}

int32_t PhyPlanFactory::genDeletePlan() {

	VOLT_DEBUG("not supported now");
	return ERROR;
}

} /* namespace expdb */


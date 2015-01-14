/*
 * UpdateExecutor.h
 *
 *  Created on: Dec 18, 2014
 *      Author: volt
 */

#ifndef UPDATEEXECUTOR_H_
#define UPDATEEXECUTOR_H_

#include "Executor.h"
#include "Expression.h"
namespace expdb {

/**
 * 需要设置操作的表对象，更新表达式；
 * 事务上下文在计划启动后设置
 */
class UpdateExecutor: public Executor {

public:

	UpdateExecutor();
	~UpdateExecutor();

	virtual int32_t open();
	virtual int32_t next(const Row *&row);
	virtual int32_t close();

	int32_t	setTable(RowTable *table){
		m_table = table;
		return SUCCESS;
	}
	int32_t setExpr(Expression exp){
		m_exp = exp;
		return SUCCESS;
	}

	int32_t addChild(Executor *childop);		//may a exec for select clause
	ExecType getType() {
		return UPDATE;
	}

	Executor *getChild(){
		return m_childop;
	}

private:
	Executor	*m_childop;
	const Row 	*m_curRow;	//记录当前访问到的行
	Expression 	m_exp;		//表达更新操作的逻辑含义，应该要输入一个行，然后计算出一个新的行出来。
	RowTable	*m_table;
};
} /* namespace expdb */

#endif /* UPDATEEXECUTOR_H_ */

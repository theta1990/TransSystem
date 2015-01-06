/*
 * Executor.h
 *
 *  Created on: Dec 16, 2014
 *      Author: volt
 */

#ifndef EXECUTOR_H_
#define EXECUTOR_H_

#include "../common.h"
#include "../storage/RowTable.h"
#include "../storage/Row.h"
#include "PhyPlan.h"
namespace expdb {

enum ExecType{
	INSERT,
	UPDATE,
	DELETE,
	READ,
	READER,
	GET
};

/***
 * 物理算子，定义执行逻辑，实质性的执行操作应该定义在其他对象里。
 */
class Executor {
public:
	Executor();

	int32_t virtual open() = 0;
	int32_t virtual next(const Row *&row) = 0;
	int32_t virtual close() = 0;
	ExecType virtual getType() = 0;
	PhyPlan * getPhyPlan(){
		return m_plan;
	}
	void setPhyPlan(PhyPlan *plan){
		m_plan = plan;
	}
	virtual Executor * getChild() = 0;
	virtual ~Executor();

private:
	PhyPlan *m_plan;
};

} /* namespace expdb */

#endif /* EXECUTOR_H_ */

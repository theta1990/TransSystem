/*
 * StoredProcedure.h
 *
 *  Created on: Feb 4, 2015
 *      Author: volt
 */

#ifndef STOREDPROCEDURE_H_
#define STOREDPROCEDURE_H_

#include "../common.h"
#include "TaskContext.h"
#include "../storage/RowObj.h"
#include "../common/memory/Allocator.h"
#include <string>
#define MAXPARAMETERS
namespace expdb {

class ResultSet {

public:
	inline void addRow(const Row &row){

	}
};

/**
 * 实际的存储过程逻辑
 */
class StoredProcedure {
public:
	StoredProcedure();

	virtual int32_t run(RowObj *objList, uint32_t size,
			TaskContext *ctx) = 0;

	virtual std::string getProcedureName() const = 0;
protected:

	/**
	 * 执行一个查询计划
	 * 正确的返回值是END。结果保存在results中。
	 * 如果是其他的返回值，就要考虑是不是要回滚。
	 */
	int32_t executePhyPlan(PhyPlan &plan, TaskContext *ctx,
			ResultSet *&results);
};

/**
 * 工作线程的处理对象
 */
class StoredProcedureTask {
public:
	StoredProcedureTask();
	StoredProcedureTask(StoredProcedure *spRef, RowObj *objList, uint32_t sz);

	int32_t run();

	int32_t setAlloc(Allocator *alloc) {
		m_alloc = alloc;
		return SUCCESS;
	}

	int32_t getContext(const TaskContext *&ctx) {

		if (m_ctx == NULL) {
			return ERROR;
		} else {
			ctx = m_ctx;
			return SUCCESS;
		}
	}

	int32_t getTranId() {

		return m_tranId;
	}

	int32_t destroy() {
		free(m_objList);
		return SUCCESS;
	}

	std::string getProcedureName() const {
		return m_spRef->getProcedureName();
	}
private:
	RowObj *m_objList;
	uint32_t m_size;
	StoredProcedure *m_spRef;
	int32_t m_tranId;
	TaskContext *m_ctx;
	Allocator *m_alloc;
};

} /* namespace expdb */

#endif /* STOREDPROCEDURE_H_ */

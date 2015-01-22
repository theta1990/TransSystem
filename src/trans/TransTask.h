/*
 * TransTask.h
 *
 *  Created on: Dec 5, 2014
 *      Author: volt
 */

#ifndef TRANSTASK_H_
#define TRANSTASK_H_

//#include "Operation.h"

#include "../common.h"
#include "../exec/PhyPlan.h"
#include "../exec/PhyPlanFactory.h"
namespace expdb {

#define MAXTRANSIZE 64

class TransTaskFactory;

class TransTask {
public:
	TransTask();
	TransTask(const TransTask &obj);
	const unsigned int getSize() {

		return m_size;
	}
	const unsigned int getTranId() {

		return m_tranId;
	}
	unsigned int getPro() {

		return m_pro;
	}
	int setPro(unsigned int pro) {

		int ret = SUCCESS;
		if (m_pro > pro || pro > m_size) {

			ret = ERROR;
		} else {

			m_pro = pro;
		}
		return ret;
	}

	PhyPlan *getNextPlan() {

		return m_pro < m_size ? m_planlist[m_pro++] : NULL;
	}

	int32_t addPhyPlan(PhyPlan *plan) {
		m_planlist[m_size++] = plan;
		return SUCCESS;
	}
	int32_t setTranId(uint32_t tranId);

	void clear() {
		m_size = 0;
		m_pro = 0;
	}

	void reset() {
		m_pro = 0;
		for (uint32_t i = 0; i < m_size; ++i)
			m_planlist[i]->reset();
	}
	void destroy();

	friend class TransTaskFactory;
private:

	unsigned int m_size;
	PhyPlan* m_planlist[MAXTRANSIZE];
	unsigned int m_pro;	//已经完成的计划数量
	unsigned int m_tranId;	//事务号
};

} /* namespace expdb */

#endif /* TRANSTASK_H_ */

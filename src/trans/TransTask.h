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


typedef int32_t (*parser)(TransTask &task, RowObj* objList, uint32_t size);
class RawTask{
public:
	int32_t parse(TransTask &task){
		if( NULL == m_parser ) {
			VOLT_WARN("task parser is not specified");
			return ERROR;
		}else {
			return m_parser(task, m_objList, m_size);
		}
	}

	RawTask() : m_parser(NULL), m_objList(NULL), m_size(0){

	}

	RawTask(parser parser_, RowObj *objList, uint32_t size) :
			m_parser(parser_), m_objList(objList), m_size(size) {

	}

	RawTask(const RawTask &obj){
		m_parser = obj.m_parser;
		m_objList = obj.m_objList;
		m_size = obj.m_size;
	}

	void destroy(){
		if( m_objList != NULL ) {
			free(m_objList);
			m_objList = NULL;
			m_size = 0;
		}
	}
private:
	parser m_parser;
	RowObj *m_objList;
	uint32_t m_size;
};

} /* namespace expdb */

#endif /* TRANSTASK_H_ */

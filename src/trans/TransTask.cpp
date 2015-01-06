/*
 * TransTask.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: volt
 */

#include "TransTask.h"
#include "../common.h"
#include <string.h>
namespace expdb {

TransTask::TransTask() :
		m_size(0), m_pro(0), m_tranId(0) {

	memset(m_planlist, 0, sizeof(m_planlist));
}

TransTask::TransTask(const TransTask& obj) {

	this->m_size = obj.m_size;
	this->m_pro = obj.m_pro;
	this->m_tranId = obj.m_tranId;
	for (uint32_t i = 0; i < m_size; ++i) {
		m_planlist[i] = obj.m_planlist[i];
	}
}

int32_t TransTask::setTranId(uint32_t tranId) {

	m_tranId = tranId;
	return SUCCESS;
}

void TransTask::destroy(){

	for(uint32_t i = 0; i < m_size; ++i){

		PhyPlanFactory::getInstance()->deletePlan(m_planlist[i]);
	}
	m_size = 0;
	m_pro = 0;
}

} /* namespace expdb */


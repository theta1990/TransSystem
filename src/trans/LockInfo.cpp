/*
 * LockInfo.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: volt
 */

#include "LockInfo.h"

namespace expdb {

LockInfo::LockInfo() {
	// TODO Auto-generated constructor stub

}

LockInfo::~LockInfo() {
	// TODO Auto-generated destructor stub
}

RCLockInfo::RCLockInfo(std::vector<CallbackTask> &vec) : m_cbTasks(vec) {

}

int32_t RCLockInfo::transBegin() {

	return SUCCESS;
}

int32_t RCLockInfo::readBegin(RowValue*& value) {

	int32_t ret = SUCCESS;

	if( (ret = value->m_lock.lock()) != SUCCESS) {
		VOLT_DEBUG("lock failed");
	}else {
		m_cbTasks.push_back(CallbackTask(value));
	}

	return ret;
}

int32_t RCLockInfo::writeBegin(RowValue*& value) {

	int32_t ret = SUCCESS;

	if( (ret = value->m_lock.lock()) != SUCCESS){
		VOLT_DEBUG("lock failed");
	}else {
		m_cbTasks.push_back(CallbackTask(value));
	}

	return ret;
}

RCLockInfo::~RCLockInfo() {

}

} /* namespace expdb */

/*
 * QLock.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: volt
 */

#include "QLock.h"
#include "../common/atomic.h"
#include "../clock.h"
namespace expdb {

QLock::QLock() : m_lock(0) {
	// TODO Auto-generated constructor stub

}

QLock::~QLock() {
	// TODO Auto-generated destructor stub
}

} /* namespace expdb */

int32_t expdb::QLock::try_lock() {

	int32_t ret = SUCCESS;

	if( 0 != m_lock ){

		ret = ERROR;
	}else {

		if( 0 !=  atomic::atomic_compare_exchange(&m_lock, 1, 0) ) {

			ret = ERROR;
		}
	}

	return ret;
}

int32_t expdb::QLock::lock() {

	int32_t ret = SUCCESS;
	uint64_t beginTime = getCycleCount();
	while( true ) {

		if( 0 == atomic::atomic_compare_exchange(&m_lock, 1, 0) ){
			break;
		}else if( getCycleCount() - beginTime > m_TIMEOUT ){

			ret = ERROR;
			break;
		}
	}
	return ret;
}

int32_t expdb::QLock::unlock() {

	int32_t ret = SUCCESS;
	if( 1 != atomic::atomic_compare_exchange(&m_lock, 0, 1) ){
		VOLT_ERROR("lock is not hold");
		ret = ERROR;
	}
	return ret;
}

int32_t expdb::QLock::lock_block() {

	int32_t ret = SUCCESS;
	while( true ) {

		if( 0 == atomic::atomic_compare_exchange(&m_lock, 1, 0) ){
			break;
		}
	}
	return ret;
}

int32_t expdb::QLock::reset() {

	m_lock = 0;
	return SUCCESS;
}

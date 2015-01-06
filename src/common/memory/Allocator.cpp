/*
 * Allocator.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: volt
 */

#include "Allocator.h"
#include "../atomic.h"
#include <assert.h>
#include <stdlib.h>
namespace expdb {

Allocator::Allocator(): m_storage(NULL), m_size(0), m_allocSize(0), m_offset(0){

}

//Allocator::Allocator(uint64_t allocSize) :
//		m_storage(NULL), m_size(0), m_allocSize(allocSize), m_offset(0) {
//
//}

Allocator::~Allocator() {
	// TODO Auto-generated destructor stub
	if (m_storage != NULL) {
		free(m_storage);
	}
	m_size = 0;
}



void expdb::Allocator::init(uint32_t allocSze) {

	m_allocSize = allocSze;
	if( NULL != m_storage ){
		VOLT_ERROR("reinit the allocator");
	}else{
		m_storage = (char *)malloc(DEFALUT_POOL_SIZE);
		m_size = DEFALUT_POOL_SIZE;
		m_offset = 0;
	}
}


} /* namespace expdb */



/*
 * PhyPlan.cpp
 *
 *  Created on: Dec 25, 2014
 *      Author: volt
 */

#include "PhyPlan.h"
#include "Executor.h"
namespace expdb {

PhyPlan::PhyPlan() : m_query(NULL), m_ctx(NULL){
	// TODO Auto-generated constructor stub

}

PhyPlan::~PhyPlan() {

	if( m_query != NULL ){
		VOLT_WARN("Memory leak here");
	}
}

int32_t PhyPlan::destory(Allocator &alloc){

	int32_t ret = SUCCESS;
	Executor *exec = m_query;
	Executor *nxt = NULL;
	while (NULL != exec) {
		nxt = exec->getChild();
		exec->destroy();		//采用placement new时，需要显示调用析构函数。
//		exec->~Executor();
		alloc.free(exec);
		exec = nxt;
	}
	m_query = NULL;
	return ret;
}

} /* namespace expdb */

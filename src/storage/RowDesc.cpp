/*
 * RowDesc.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: volt
 */

#include "RowDesc.h"
#include "RowObj.h"
namespace expdb {

RowDesc::RowDesc() : m_priIdx(0), m_colCnt(0) {
	// TODO Auto-generated constructor stub

}

RowDesc::~RowDesc() {
	// TODO Auto-generated destructor stub
}



void RowDesc::addRowType(RowType type) {

	m_type[m_colCnt++] = type;
}

uint32_t RowDesc::getColCnt() const{

	return m_colCnt;
}

uint32_t RowDesc::getRowLen() const{

	uint32_t ret = 0;

	for(uint32_t i = 0; i < m_colCnt; ++i){

		ret += RowObj::getSize(m_type[i]);
	}

	return ret;
}

RowType RowDesc::getRowtype(uint32_t colIdx)const {

	if( colIdx < m_colCnt )
		return m_type[colIdx];
	else return SMALLINT;
}

void RowDesc::dump() const{

	for(uint32_t i=0;i<m_colCnt;++i){
		printf("Col %d, type %s\n", i, TypeName[m_type[i]]);
	}
}


} /* namespace expdb */


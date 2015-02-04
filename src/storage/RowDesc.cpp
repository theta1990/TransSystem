/*
 * RowDesc.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: volt
 */

#include "RowDesc.h"
#include "RowObj.h"
namespace expdb {

RowDesc::RowDesc() : m_colCnt(0), m_totalLen(0){
	// TODO Auto-generated constructor stub

}

RowDesc::~RowDesc() {
	// TODO Auto-generated destructor stub
}



int32_t RowDesc::addRowType(RowType type, uint32_t len) {

	int32_t ret = SUCCESS;
	if( type == STR ){
		if( len == 0 ) {
			VOLT_ERROR("Can not set the length of string to 0");
			ret = ERROR;
		}else {
			m_len[m_colCnt] = len;
		}
	}else {
		m_len[m_colCnt] = RowObj::getSize(type);
	}
	if( SUCCESS == ret ){
		m_totalLen += m_len[m_colCnt];
		m_type[m_colCnt++] = type;
	}
	return ret;
}

int32_t RowDesc::addRowType(RowType type, std::string str, uint32_t len) {

	int32_t ret = SUCCESS;

	if( type == STR ){
		if( len == 0 ) {
			VOLT_ERROR("Can not set the length of string to 0");
			ret = ERROR;
		}else {
			m_len[m_colCnt] = len;
		}
	}else {
		m_len[m_colCnt] = RowObj::getSize(type);
	}
	if( SUCCESS == ret ){
		m_totalLen += m_len[m_colCnt];
		m_colName[m_colCnt] = str;
		m_type[m_colCnt++] = type;
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


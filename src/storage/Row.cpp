/*
 * Row.cpp
 *
 *  Created on: Dec 10, 2014
 *      Author: volt
 */

#include "Row.h"
#include "../common/serialization.h"
#include <assert.h>
namespace expdb {

Row::Row() :
		m_desc(NULL) {
	// TODO Auto-generated constructor stub

}

Row::Row(const RowDesc *desc) :
		m_desc(desc) {

}

Row::~Row() {
	// TODO Auto-generated destructor stub
}

void Row::setDesc(const RowDesc *desc) {

	m_desc = desc;
}

//void Row::addCol(RowObj obj) {
//
//	assert(obj.m_type == m_desc->getRowtype(m_colCnt));
//	m_col[m_colCnt++] = obj;
//}

void Row::dump() const {

	assert(m_desc != NULL);
	for (uint32_t i = 0; i < m_desc->getColCnt(); ++i) {
		m_col[i].dump();
		printf(" ");
	}
	printf("\n");
}

int Row::serilization(char* buf, const int64_t buf_len, int64_t& pos) const {

	//we don't contain the row description here, just raw data
	int ret = SUCCESS;
	if (m_desc == NULL) {
		VOLT_ERROR("Row Object does not contains column description");
		ret = ERROR;
	} else if (pos + m_desc->getRowLen() > buf_len) {

		VOLT_DEBUG("buffer overflow");
		ret = ERROR;
	} else {

		for (uint32_t i = 0; i < m_desc->getColCnt(); ++i) {

			switch (m_col[i].m_type) {
			case SMALLINT:
				expdb::encode_i16(buf, buf_len, pos, m_col[i].m_value.smallint);
				break;
			case MIDINT:
				expdb::encode_i32(buf, buf_len, pos, m_col[i].m_value.midint);
				break;
			case BIGINT:
				expdb::encode_i64(buf, buf_len, pos, m_col[i].m_value.bigint);
				break;
			case CHAR:
				expdb::encode_i8(buf, buf_len, pos, m_col[i].m_value.cvalue);
				break;
			case BVALUE:
				expdb::encode_bool(buf, buf_len, pos, m_col[i].m_value.bvalue);
				break;
			default:
				break;
			}
		}
	}
	return ret;
}

void Row::addCol(RowObj obj, int colId) {

	assert(colId < m_desc->getColCnt());
	m_col[colId] = obj;
}

/**
 * 函数调用，传递形参的时候会被调用
 */
Row::Row(const Row& obj) {

	m_desc = obj.m_desc;
	for (uint32_t i = 0; i < m_desc->getColCnt(); ++i) {
		m_col[i] = obj.m_col[i];
	}
}

/**
 * 赋值操作时被调用
 */
const Row& Row::operator =(const Row& obj) {

	m_desc = obj.m_desc;
	assert(m_desc != NULL);
	for (uint32_t i = 0; i < m_desc->getColCnt(); ++i) {
		m_col[i] = obj.m_col[i];
	}
	return *this;
}

bool Row::assign(const Row &obj){

	m_desc = obj.m_desc;
	assert(m_desc != NULL);
	for (uint32_t i = 0; i < m_desc->getColCnt(); ++i) {
		m_col[i] = obj.m_col[i];
	}
	return true;
}

int32_t Row::getCol(int32_t colId, RowObj &obj) const {

	int32_t ret = SUCCESS;
	if (colId >= m_desc->getColCnt()) {

		VOLT_DEBUG("col id out of range, %d", colId);
		ret = ERROR;
	} else {

		obj = m_col[colId];
	}
	return ret;
}

int32_t Row::setCol(int32_t colId, const RowObj &obj) {

	int32_t ret = SUCCESS;

	if (colId >= m_desc->getColCnt()) {

		VOLT_DEBUG("col id out of range, %d", colId);
		ret = ERROR;
	} else {

		m_col[colId] = obj;
	}
	return ret;
}

int Row::deserilization(const char* buf, const int64_t buf_len, int64_t& pos) {

	int ret = SUCCESS;

	if ( NULL == m_desc) {
		VOLT_ERROR("row schema is not provided");
		ret = ERROR;
	} else {

		uint32_t colCnt = m_desc->getColCnt();
		for (uint32_t i = 0; i < colCnt; ++i) {

			m_col[i].m_type = m_desc->getRowtype(i);
			switch (m_col[i].m_type) {
			case SMALLINT:
				ret = expdb::decode_i16(buf, buf_len, pos,
						(int16_t *) &m_col[i].m_value.smallint);
				break;
			case MIDINT:
				ret = expdb::decode_i32(buf, buf_len, pos,
						(int32_t *) &m_col[i].m_value.midint);
				break;
			case BIGINT:
				ret = expdb::decode_i64(buf, buf_len, pos,
						(int64_t *) (&m_col[i].m_value.bigint));
				break;
			case CHAR:
				ret = expdb::decode_i8(buf, buf_len, pos,
						(int8_t*) (&m_col[i].m_value.cvalue));
				break;
			case BVALUE:
				ret = expdb::decode_bool(buf, buf_len, pos,
						&m_col[i].m_value.bvalue);
				break;
			default:
				break;
			}
		}
	}
	return ret;
}

int32_t Row::getRowKey(RowKey& key) const {

	assert(m_desc != NULL);
	const int32_t * priIdx = m_desc->getPriIdx();

	int8_t &i = key.m_size;
	i = 0;
	while( priIdx[i] != -1 && i < 8 ) {

		key.m_keys[i] = m_col[priIdx[i]];
		++i;
	}
	return SUCCESS;
}

} /* namespace expdb */


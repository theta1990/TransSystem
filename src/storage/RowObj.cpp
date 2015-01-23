/*
 * RowObj.cpp
 *
 *  Created on: Dec 10, 2014
 *      Author: volt
 */

#include "RowObj.h"
#include "../common/murmur_hash.h"
#include "../common/serialization.h"
#include <assert.h>
namespace expdb {

char TypeName[][16] = { "int16", "int32", "int64", "char", "bool" };

RowObj::Add RowObj::addfunc;
RowObj::Minus RowObj::minusfunc;
RowObj::Multiple RowObj::mulfunc;
RowObj::Divide RowObj::divfunc;
RowObj::Assign RowObj::assifunc;

RowObj::RowObj() :
		m_type(SMALLINT) {
	m_value.bigint = 0;
}

RowObj::RowObj(uint16_t si) :
		m_type(SMALLINT) {

	m_value.smallint = si;
}

RowObj::RowObj(uint32_t mi) :
		m_type(MIDINT) {
	m_value.midint = mi;
}

RowObj::RowObj(uint64_t bi) :
		m_type(BIGINT) {
	m_value.bigint = bi;
}

RowObj::RowObj(bool bo) :
		m_type(BVALUE) {
	m_value.bvalue = bo;
}

RowObj::~RowObj() {

	if (m_type == STR) {
		if (m_value.str != NULL)
			free(m_value.str);
	}
}

uint64_t RowObj::hash() const {

	uint64_t ret;
	switch (m_type) {
	case SMALLINT:
		ret = tools::murmurhash64A(&m_value.smallint, sizeof(uint16_t), 0);
		break;
	case MIDINT:
		ret = tools::murmurhash64A(&m_value.midint, sizeof(uint32_t), 0);
		break;
	case BIGINT:
		ret = tools::murmurhash64A(&m_value.bigint, sizeof(uint64_t), 0);
		break;
	case STR:
		if (m_value.str == NULL) {
			VOLT_ERROR("Object has a null pointer with fix string");
			ret = 0;
		} else
			ret = tools::murmurhash64A(&m_value.str->m_str, m_value.str->m_size, 0);
		break;
	case BVALUE:
		ret = tools::murmurhash64A(&m_value.bvalue, sizeof(bool), 0);
		break;
	default:
		ret = 0;
		break;
	}
	return ret;
}

RowObj RowObj::op(OpType type, const RowObj &base, const RowObj &obj) {

	RowObj ret;
	assert(base.m_type == obj.m_type);
	ret.m_type = base.m_type;
	switch (type) {
	case ADD:
		ret = addfunc(base, obj);
		break;
	case MIN:
		ret = minusfunc(base, obj);
		break;
	case MUL:
		ret = mulfunc(base, obj);
		break;
	case DIV:
		ret = divfunc(base, obj);
		break;
	case ASSI:
		ret = assifunc(base, obj);
		break;
	default:
		VOLT_ERROR("not supported")
		;
		assert(0);
	}
	return ret;
}

bool RowObj::operator >(const RowObj& obj) const {

	bool ret = false;
	assert(m_type == obj.m_type);
	switch (m_type) {
	case SMALLINT:
		ret = m_value.smallint > obj.m_value.smallint;
		break;
	case MIDINT:
		ret = m_value.midint > obj.m_value.midint;
		break;
	case BIGINT:
		ret = m_value.bigint > obj.m_value.bigint;
		break;
	case STR:
		if (m_value.str == NULL || obj.m_value.str == NULL) {
			VOLT_ERROR("Object has a null pointer with fix string");
		} else
			ret = (strcmp(m_value.str->m_str, obj.m_value.str->m_str) > 0);
		break;
	case BVALUE:
		ret = m_value.bvalue > obj.m_value.bvalue;
		break;
	default:
		break;
	}
	return ret;
}

bool RowObj::operator ==(const RowObj &obj) const {

	bool ret = false;
	assert(m_type == obj.m_type);
	switch (m_type) {
	case SMALLINT:
		ret = m_value.smallint == obj.m_value.smallint;
		break;
	case MIDINT:
		ret = m_value.midint == obj.m_value.midint;
		break;
	case BIGINT:
		ret = m_value.bigint == obj.m_value.bigint;
		break;
	case STR:
		if (m_value.str == NULL || obj.m_value.str == NULL) {
			VOLT_ERROR("Object has a null pointer with fix string");
		} else
			ret = (strcmp(m_value.str->m_str, obj.m_value.str->m_str) == 0);
		break;
	case BVALUE:
		ret = m_value.bvalue == obj.m_value.bvalue;
		break;
	default:
		break;
	}
	return ret;
}

void RowObj::dump() const {

	switch (m_type) {
	case SMALLINT:
		printf("small int: %d", m_value.smallint);
		break;
	case MIDINT:
		printf("mid int: %d", m_value.midint);
		break;
	case BIGINT:
		printf("big int: %ld", m_value.bigint);
		break;
	case STR:
		if (m_value.str->m_str == NULL)
			printf("char: <nil>");
		else
			printf("char: %s", m_value.str->m_str);
		break;
	case BVALUE:
		printf("bool: %d", m_value.bvalue);
		break;
	default:
		break;
	}
}

//void RowObj::serilization(char* buf, const int64_t buf_len, int64_t& pos) {
//
//	expdb::encode_i8(buf, buf_len, pos, m_type);
//	switch (m_type) {
//	case SMALLINT:
//		expdb::encode_i16(buf, buf_len, pos, m_value.smallint);
//		break;
//	case MIDINT:
//		expdb::encode_i32(buf, buf_len, pos, m_value.midint);
//		break;
//	case BIGINT:
//		expdb::encode_i64(buf, buf_len, pos, m_value.bigint);
//		break;
//	case CHAR:
//		expdb::encode_i8(buf, buf_len, pos, m_value.cvalue);
//		break;
//	case BVALUE:
//		expdb::encode_bool(buf, buf_len, pos, m_value.bvalue);
//		break;
//	default:
//		break;
//	}
//}

//void RowObj::deserilization(const char* buf, const int64_t buf_len,
//		int64_t& pos) {
//
//	int8_t v;
//	expdb::decode_i8(buf, buf_len, pos, &v);
//	m_type = RowType(v);
//	switch (m_type) {
//	case SMALLINT:
//		expdb::decode_i16(buf, buf_len, pos, (int16_t *) &m_value.smallint);
//		break;
//	case MIDINT:
//		expdb::decode_i32(buf, buf_len, pos, (int32_t *) &m_value.midint);
//		break;
//	case BIGINT:
//		expdb::decode_i64(buf, buf_len, pos, (int64_t *) (&m_value.bigint));
//		break;
//	case CHAR:
//		expdb::decode_i8(buf, buf_len, pos, (int8_t*) (&m_value.cvalue));
//		break;
//	case BVALUE:
//		expdb::decode_bool(buf, buf_len, pos, &m_value.bvalue);
//		break;
//	default:
//		break;
//	}
//}

uint32_t RowObj::getSize(RowType type){

	int ret = 0;
	switch (type) {
	case SMALLINT:
		ret = sizeof(int16_t);
		break;
	case MIDINT:
		ret = sizeof(int32_t);
		break;
	case BIGINT:
		ret = sizeof(int64_t);
		break;
	case STR:
		ret = 0;
		break;
	case BVALUE:
		ret = sizeof(bool);
		break;
	default:
		break;
	}
	return ret;
}

} /* namespace expdb */


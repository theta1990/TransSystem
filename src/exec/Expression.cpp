/*
 * Expression.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: volt
 */

#include "Expression.h"

namespace expdb {

Expression::Expression() :m_colId(0), m_type(ADD), m_arg(), m_out() {
	// TODO Auto-generated constructor stub

}

Expression::Expression(int32_t colId, OpType type) : m_colId(colId), m_type(type), m_arg(), m_out() {

}

Expression::Expression(const Expression &expr){
	m_colId = expr.m_colId;
	m_type = expr.m_type;
	m_arg = expr.m_arg;
}

const Expression & Expression::operator =(const Expression &expr){

	m_colId = expr.m_colId;
	m_type = expr.m_type;
	m_arg = expr.m_arg;
	return *this;
}

int32_t Expression::cal(const Row* in, const Row*& out) {

	int32_t ret = SUCCESS;

	m_out.assign(*in);

	RowObj ov;
	m_out.getCol(m_colId, ov);
	RowObj nv = RowObj::op(m_type, ov, m_arg);

	m_out.setCol(m_colId, nv);
	out = &m_out;

	return ret;
}

int32_t Expression::setArg(RowObj arg) {

	m_arg = arg;
	return SUCCESS;
}

int32_t Expression::setType(OpType type) {

	m_type = type;
	return SUCCESS;
}

Expression::~Expression() {
	// TODO Auto-generated destructor stub
}

} /* namespace expdb */

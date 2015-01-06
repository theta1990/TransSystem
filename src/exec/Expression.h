/*
 * Expression.h
 *
 *  Created on: Dec 22, 2014
 *      Author: volt
 */

#ifndef EXPRESSION_H_
#define EXPRESSION_H_
#include "../common.h"
#include "../storage/RowObj.h"
#include "../storage/Row.h"

namespace expdb {

class Expression {
public:
	Expression();
	Expression(int32_t colId, OpType type);
	int32_t setArg(RowObj arg);
	int32_t setType(OpType type);
	int32_t cal(const Row *in, const Row *&out);	//输入一个行，计算出一个新的行返回
	virtual ~Expression();

private:

	int32_t	m_colId;//need to be more complex to describe arithmetic
	OpType	m_type;	//need to be more complex to describe arithmetic
	RowObj	m_arg;	//need to be more complex to describe arithmetic
	Row		m_out;
};

} /* namespace expdb */

#endif /* EXPRESSION_H_ */

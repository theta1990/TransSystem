/*
 * RowObj.h
 *
 *  Created on: Dec 10, 2014
 *      Author: volt
 */

#ifndef ROWOBJ_H_
#define ROWOBJ_H_

#include "../common.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <string>
namespace expdb {

enum RowType {
	SMALLINT = 0, MIDINT = 1, BIGINT = 2, STR = 3, BVALUE = 4, DOUBLE = 5
};

enum OpType {
	ADD,		//加上一个值
	MIN,		//减去一个值
	MUL,		//乘上一个值
	DIV,		//除以一个值
	ASSI		//赋值
};

extern char TypeName[][16];
/**
 * 代表行中的取值，自描述的数据类型
 */

class Row;

struct CharFixLen{

	int32_t	m_size;
	char	m_str[0];
};


class RowObj {
public:
	RowObj();

	RowObj(uint16_t si);
	RowObj(uint32_t mi);
	RowObj(uint64_t bi);
	RowObj(char ch);
	RowObj(bool bo);
	RowObj(double d);
	RowObj(const char *str, int32_t len);
	virtual ~RowObj();
	uint64_t hash() const;

	inline void setSmallInt(uint16_t value);
	inline void setMidInt(uint32_t value);
	inline void setBigInt(uint64_t value);
	inline void setBool(bool value);
	inline void setDouble(double value);
	inline uint16_t getSmallInt();
	inline uint32_t getMidInt();
	inline uint64_t getBigInt();
	inline bool getbool();

	inline void setString(const char *str, int32_t length);
//	inline void setDecimal(const char *str, int32_t s, int32_t p);

	void clear() {

		if( (m_type == STR) && m_value.str != NULL ){
			free(m_value.str);
			m_value.str = NULL;
		}
		m_type = BIGINT;
		m_value.bigint = 0;
	}

	int32_t allocForString(int32_t length) {

		int32_t ret = SUCCESS;

		if( length <= 0 ) {
			ret = ERROR;
			VOLT_ERROR("Can not set the string length to 0");
		}

		if( SUCCESS == ret ){
			clear();
			m_value.str = (CharFixLen *)malloc(length + sizeof(CharFixLen));
			m_value.str->m_size = length;
			m_type = STR;
		}
		return ret;
	}

	RowObj(const RowObj &obj) : m_type(SMALLINT){

		assign(obj);
	}
	const RowObj & operator = (const RowObj &obj){
		assign(obj);
		return *this;
	}



	RowType getType() const {
		return m_type;
	}

	bool operator >(const RowObj &obj) const;
	bool operator ==(const RowObj &obj) const;

	void dump() const;

	std::string toString() const{

		std::string str;
		char buf[128];
		switch (m_type) {
		case SMALLINT:
			sprintf(buf, "%d[SI]", m_value.smallint);
			break;
		case MIDINT:
			sprintf(buf, "%d[MI]", m_value.midint);
			break;
		case BIGINT:
			sprintf(buf, "%ld[BI]", m_value.bigint);
			break;
		case STR:
			if (m_value.str->m_str == NULL)
				sprintf(buf, "<nil>[CH]");
			else
				sprintf(buf,"%s[CH]", m_value.str->m_str);
			break;
		case BVALUE:
			sprintf(buf, "%d[BO]", m_value.bvalue);
			break;
		case DOUBLE:
			sprintf(buf, "%lf[DLE]", m_value.dval);
			break;
		default:
			break;
		}
		str.append(buf);
		return str;
	}

//	void serilization(char *buf, const int64_t buf_len, int64_t &pos);
//	void deserilization(const char *buf, const int64_t buf_len, int64_t &pos);

	static RowObj op(OpType type, const RowObj &base, const RowObj &obj);
	static uint32_t getSize(RowType type);

	struct Add {
		const RowObj operator()(const RowObj &a, const RowObj &b) {

			RowObj obj(a);		//理论上应该验证类型是不是相同吧
			switch (a.m_type) {
			case SMALLINT:
				obj.m_value.smallint += b.m_value.smallint;
				break;
			case MIDINT:
				obj.m_value.midint += b.m_value.midint;
				break;
			case BIGINT:
				obj.m_value.bigint += b.m_value.bigint;
				break;
			case STR:
				VOLT_ERROR("Does not support add for string");
				break;
			case BVALUE:
				obj.m_value.bvalue = obj.m_value.bvalue || b.m_value.bvalue;
				break;
			case DOUBLE:
				obj.m_value.dval = obj.m_value.dval + b.m_value.dval;
				break;
			default:
				VOLT_ERROR("not supported data type")
				;
			}
			return obj;
		}
	};

	struct Assign {
		const RowObj operator()(const RowObj &a, const RowObj &b) {

			assert(a.m_type == b.m_type);
			return b;
		}
	};

	struct Minus {
		const RowObj operator()(const RowObj &a, const RowObj &b) {

			RowObj obj(a);
			switch (a.m_type) {
			case SMALLINT:
				obj.m_value.smallint -= b.m_value.smallint;
				break;
			case MIDINT:
				obj.m_value.midint -= b.m_value.midint;
				break;
			case BIGINT:
				obj.m_value.bigint -= b.m_value.bigint;
				break;
			case STR:
				VOLT_ERROR("Does not support minus for str");
				break;
			case BVALUE:
				obj.m_value.bvalue = obj.m_value.bvalue || b.m_value.bvalue;
				break;
			case DOUBLE:
				obj.m_value.dval = obj.m_value.dval - b.m_value.dval;
				break;
			default:
				VOLT_ERROR("not supported data type")
				;
			}
			return obj;
		}
	};

	struct Multiple {
		const RowObj operator()(const RowObj &a, const RowObj &b) {
			assert(0);
			return RowObj();
		}
	};

	struct Divide {
		const RowObj operator()(const RowObj &a, const RowObj &b) {
			assert(0);
			return RowObj();
		}
	};

	friend class Row;
private:

	void assign(const RowObj &obj) {

		clear();
		m_type = obj.m_type;
		if( m_type == STR ){

			if( obj.m_value.str == NULL ){
				VOLT_ERROR("Object has a null pointer with fix string");
			}else {
				allocForString(obj.m_value.str->m_size);
				memcpy(m_value.str, obj.m_value.str, sizeof(CharFixLen) + obj.m_value.str->m_size);
			}
		}else {
			m_value = obj.m_value;
		}
	}

	static Add addfunc;
	static Assign assifunc;
	static Minus minusfunc;
	static Multiple mulfunc;
	static Divide divfunc;

	RowType m_type;
	union {
		uint16_t smallint;
		uint32_t midint;
		uint64_t bigint;
		bool bvalue;
		double	dval;
		CharFixLen	*str;
	} m_value;
};

void RowObj::setSmallInt(uint16_t value) {

	m_type = SMALLINT;
	m_value.smallint = value;
}

void RowObj::setMidInt(uint32_t value) {

	m_type = MIDINT;
	m_value.midint = value;
}

void RowObj::setBigInt(uint64_t value) {

	m_type = BIGINT;
	m_value.bigint = value;
}

void RowObj::setBool(bool value) {

	m_type = BVALUE;
	m_value.bvalue = value;
}

void RowObj::setDouble(double value) {

	m_type = DOUBLE;
	m_value.dval = value;
}

void RowObj::setString(const char *str, int32_t length) {

	if( strlen(str) >= static_cast<uint32_t>(length) ) {
		VOLT_ERROR("RowObj, string length out of bound");
	}else {
		clear();
		if( SUCCESS == allocForString(length) ) {

			strcpy(m_value.str->m_str, str);
			for(uint32_t i = strlen(str); i < static_cast<uint32_t>(length); ++i){
				m_value.str->m_str[i] = '\0';
			}
		}
	}
}

uint16_t RowObj::getSmallInt() {

	return m_value.smallint;
}

uint32_t RowObj::getMidInt() {

	return m_value.midint;
}

uint64_t RowObj::getBigInt() {

	return m_value.bigint;
}

bool RowObj::getbool() {

	return m_value.bvalue;
}

} /* namespace expdb */

#endif /* ROWOBJ_H_ */

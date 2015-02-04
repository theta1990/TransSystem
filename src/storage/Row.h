/*
 * Row.h
 *
 *  Created on: Dec 10, 2014
 *      Author: volt
 */

#ifndef ROW_H_
#define ROW_H_
#include "../common.h"
#include "RowObj.h"
#include "RowDesc.h"
#include "../common/murmur_hash.h"
#include <string>
namespace expdb {

/**
 * 这种组合Key的方式不好，直接导致在索引结构中，Key的空间变大了很多。我觉得可以考虑将Key也序列化，然后在索引结构中存储
 */
struct RowKey{

	int8_t m_size;
	RowObj m_keys[8];

	RowKey() : m_size(0) {

	}

	int32_t addKey(RowObj obj){

		if( m_size < 8 ) {
			m_keys[m_size++] = obj;
			return SUCCESS;
		}else {
			return ERROR;
		}
	}

	uint64_t hash() const {

		uint64_t hv[8], ret;
		for (int8_t i = 0; i < m_size; ++i) {
			hv[i] = m_keys[i].hash();
		}
		ret = tools::murmurhash64A(hv, sizeof(uint64_t) * m_size, 0);
		return ret;
	}

	bool operator ==(const RowKey &obj) const {

		bool ret = (m_size == obj.m_size);
		if (ret) {
			for (int8_t i = 0; i < m_size && ret; ++i) {
				ret = (m_keys[i] == obj.m_keys[i]);
			}
		}
		return ret;
	}

	std::string toString() const {
		std::string str;
		str.append("( ");
		for (int8_t i = 0; i < m_size; ++i) {
			str.append(m_keys[i].toString());
			i != m_size - 1 ? str.append(", ") : str.append("");
		}
		str.append(" )");
		return str;
	}

};

class Row {
public:
	Row();
	Row(const RowDesc *desc);
	virtual ~Row();

	bool assign(const Row &row);

	void setDesc(const RowDesc *desc);
//	void addCol(RowObj obj);
	void addCol(RowObj& obj, int colId);
	int32_t getCol(int32_t colId, RowObj &obj) const;
	int32_t setCol(int32_t colId, const RowObj &obj);
	void dump() const;
	int32_t getRowKey(RowKey &key) const;
	int serilization(char *buf, const int64_t buf_len, int64_t &pos) const;
	int deserilization(const char *buf, const int64_t buf_len, int64_t &pos);

private:
	Row(const Row &obj);
	const Row & operator = (const Row &obj);

	RowObj m_col[1024];
	const RowDesc *m_desc;
};

} /* namespace expdb */


#endif /* ROW_H_ */

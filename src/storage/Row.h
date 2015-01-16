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
namespace expdb {

struct RowKey{

	int8_t m_size;
	RowObj m_keys[8];


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

};

class Row {
public:
	Row();
	Row(const RowDesc *desc);
	virtual ~Row();

	bool assign(const Row &row);

	void setDesc(const RowDesc *desc);
//	void addCol(RowObj obj);
	void addCol(RowObj obj, int colId);
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

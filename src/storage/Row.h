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

namespace expdb {

typedef RowObj RowKey;

class Row {
public:
	Row();
	Row(const RowDesc *desc);
	Row(const Row &obj);
	const Row & operator = (const Row &obj);
	virtual ~Row();

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
	RowObj m_col[1024];
	const RowDesc *m_desc;
};

} /* namespace expdb */


#endif /* ROW_H_ */

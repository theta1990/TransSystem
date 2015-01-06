/*
 * RowDesc.h
 *
 *  Created on: Dec 12, 2014
 *      Author: volt
 */

#ifndef ROWDESC_H_
#define ROWDESC_H_
#include "../common.h"
#include "RowObj.h"
namespace expdb {

class RowDesc {
public:
	RowDesc();
	virtual ~RowDesc();

	void addRowType(RowType type);
	uint32_t getColCnt() const;
	uint32_t getRowLen() const;
	inline uint32_t getPriIdx() const{

		return m_priIdx;
	}
	RowType getRowtype(uint32_t colIdx) const;

	void dump() const;
private:

	uint32_t m_priIdx;
	uint32_t m_colCnt;
	RowType m_type[1024];
};

} /* namespace expdb */

#endif /* ROWDESC_H_ */

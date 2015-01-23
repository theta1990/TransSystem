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

	int32_t addRowType(RowType type, uint32_t len = 0);

	uint32_t getColCnt() const {

		return m_colCnt;
	}
	uint32_t getRowLen() const {
		return m_totalLen;
	}

	uint32_t getColLen(uint32_t colIdx) const {

		if( colIdx < m_colCnt)
			return m_len[colIdx];
		else {
			return 0;
		}
	}

	int32_t setPriIdx(int32_t *priIdx, int8_t size){

		int32_t ret = SUCCESS;
		if( size >= 8 ) {
			VOLT_ERROR("Does not support index size bigger than 7");
			ret = ERROR;
		}else {

			for (int8_t i = 0; i < size; ++i) {
				if (static_cast<uint32_t>(priIdx[i]) > m_colCnt) {
					VOLT_ERROR("Index out of bound, %d(%d)", priIdx[i],
							m_colCnt);
					ret = ERROR;
				}else {
					m_priIdx[i] = priIdx[i];
				}
			}
		}
		if( ret == SUCCESS ){
			m_priIdx[size] = -1;	//end of the index array
		}else {
			m_priIdx[0] = -1;
		}
		return ret;
	}

	const int32_t* getPriIdx() const{

		return m_priIdx;
	}

	RowType getRowtype(uint32_t colIdx) const;

	void dump() const;
private:

	int32_t m_priIdx[8];
	uint32_t m_colCnt;
	RowType m_type[1024];
	uint32_t m_len[1024];
	uint32_t m_totalLen;
};

} /* namespace expdb */

#endif /* ROWDESC_H_ */

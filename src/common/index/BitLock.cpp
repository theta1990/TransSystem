/*
 * BitLock.cpp
 *
 *  Created on: Dec 11, 2014
 *      Author: volt
 */

#include "BitLock.h"

namespace expdb {

BitLock::BitLock() :  m_size(0), m_bits(NULL){
	// TODO Auto-generated constructor stub

}

BitLock::~BitLock() {
	// TODO Auto-generated destructor stub
	destroy();
}

} /* namespace expdb */

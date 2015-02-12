/*
 * TransIdGenerator.cpp
 *
 *  Created on: Feb 10, 2015
 *      Author: volt
 */

#include "TransIdGenerator.h"

namespace expdb {

volatile uint32_t TransIdGenerator::globalId = 0;

TransIdGenerator::TransIdGenerator() {
	// TODO Auto-generated constructor stub

}

TransIdGenerator::~TransIdGenerator() {
	// TODO Auto-generated destructor stub
}

} /* namespace expdb */

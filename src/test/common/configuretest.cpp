/*
 * configuretest.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: volt
 */

#include "test.h"
#include "../../Configure.h"
using namespace expdb;

int testconfigure(int argc, char **argv){

	Configure *config = Configure::getInstance();
	config->dump();
	return 0;
}
//TEST(testconfigure);


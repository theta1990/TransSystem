/*
 * test.h
 *
 *  Created on: Dec 18, 2014
 *      Author: volt
 */


typedef int (*testfunc)(int , char **);

extern testfunc func;
#define TEST(arg) testfunc func = arg

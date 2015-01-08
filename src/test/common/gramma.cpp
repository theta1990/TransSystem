/*
 * gramma.cpp
 *
 *  Created on: Dec 19, 2014
 *      Author: volt
 */
#include "test.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void pointer(const int *&a){

	printf("%d", *a);
}

int f = 0;
int x = 10;

void *func1(void *para){

	printf("func1\n");
	while( f == 0 ){
	}
	printf("%d\n", x);
	return NULL;
}

void *func2(void *para){

	printf("func2\n");
	x = 20;
	f = 1;
	return NULL;
}


//int testRef(int &a){
//
//	printf("%d", a);
//}

int testRef(int *&a){

	printf("%d", *a);
}

int grammaTest(int argc, char **argv){

//	int a = 0;
////	const int *ref = &a;
//	int *pa = &a;
//	int *&ref = pa;
////	int *&ref1 = &a;
//	int * const ref2 = pa;
//
////	const int *&cref = (const int *)&a;
//	printf("%d", *ref);
//
//	a ++;
//
//	printf("%d", *ref);

	int *a = new int;
	*a = 10;
	int b = 10;
//	testRef(&b);

//	pthread_t h1, h2;
//	pthread_create(&h1, NULL, &func1, NULL);
//	pthread_create(&h2, NULL, &func2, NULL);
//
//	pthread_join(h1, NULL);
//	pthread_join(h2, NULL);
	return 0;
}
//TEST(grammaTest);

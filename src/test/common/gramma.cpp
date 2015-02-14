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

template <class T>
class Array {
public:
	Array(int lowBound, int highBound);
	Array(int size);

	T & operator [](int index);

//	bool operator == (const Array<int> &lhs, const Array<int> &rhs);
};



int grammaTest(int argc, char **argv){



//	int a = 0;
//	const int *ref = &a;
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

//	int *a = new int;
//	*a = 10;
//	int b = 10;

//	Array<int> a(10);
//	Array<int> b(10);

//	for(int i = 0; i<10;++i)
//		if( a == static_cast< Array<int> >(b[i]) ) {
//			printf("yes");
//		}

//	int a = 1;
//	printf("%x", ~a);

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

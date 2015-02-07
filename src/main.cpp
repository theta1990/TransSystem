/*
 * main.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: volt
 */

#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include "common.h"
#include "debuglog.h"
#include "clock.h"
#include "Configure.h"
using namespace std;

//int main(int argc, char **argv) {
//
//	int wCnt, opt;
//	unsigned int lockCnt, taskSize, num;
//	expdb::Configure configure;
//	expdb::TransExecQueue **w;
//	expdb::TransTaskFactory* f;
//	expdb::LockMgr *lockmgr;
//	expdb::StatCollector stat;
//
//	while (-1 != (opt = getopt(argc, argv, "l:w:t:c:"))) {
//
//		switch (opt) {
//		case 'l':
//			lockCnt = strtol(optarg, NULL, 10);
//			configure.setDbSize(lockCnt);
//			break;
//		case 'w':
//			wCnt = strtol(optarg, NULL, 10);
//			configure.setThreadCnt(wCnt);
//			break;
//		case 't':
//			taskSize = strtol(optarg, NULL, 10);
//			configure.setTaskSize(taskSize);
//			break;
//		case 'c':
//			num = strtol(optarg, NULL, 10);
//			break;
//		default:
//			VOLT_ERROR("unknown cmd %c, %s", opt, optarg)
//			;
//		}
//	}
//
//	lockmgr = new expdb::LockMgr(lockCnt);
//	w = new expdb::TransExecQueue*[wCnt];
//	f = new expdb::TransTaskFactory(taskSize, lockCnt);
//
//	for (int i = 0; i < wCnt; ++i) {
//		w[i] = new expdb::TransExecQueue();
//		w[i]->setLockMgr(lockmgr);
//	}
//
//	for (unsigned int i = 0; i < num; ++i) {
//		w[i % wCnt]->push(f->genTask());
//	}
//
//	stat.start();
//
//
//	for(int i=0; i<wCnt;++i){
//		w[i]->start();
//	}
//
//	for (int i = 0; i < wCnt; ++i) {
//		w[i]->stop();
//	}
//
//	for (int i = 0; i < wCnt; ++i) {
//		w[i]->join();
//	}
//	stat.stop();
//
//	for( int i=0;i<wCnt;++i){
//
//		stat.gather(w[i]->getStat());
//		delete w[i];
//	}
//
//	configure.report();
//	stat.report();
//
////	VOLT_INFO("total cost: %lld", end - start);
//	delete w;
//	delete f;
//	delete lockmgr;
//
//	return 0;
//}

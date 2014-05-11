/*
 * CacheThread.h
 *
 *  Created on: May 11, 2014
 *      Author: wang
 */

#ifndef CACHETHREAD_H_
#define CACHETHREAD_H_
#include "Thread.h"
#include "CacheQuery.h"
class CacheThread:public Thread {
public:
	CacheThread(std::size_t interval);
	virtual ~CacheThread();
	void run() ; //继承线程的函数
private:
	void process();
	std::size_t _interval ;
};

#endif /* CACHETHREAD_H_ */

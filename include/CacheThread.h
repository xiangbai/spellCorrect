/*
 * CacheThread.h
 *
 *  Created on: May 11, 2014
 *      Author: wang
 */

#ifndef CACHETHREAD_H_
#define CACHETHREAD_H_
#include "Thread.h"

#include <vector>
class CacheQuery ;
class CacheThread:public Thread {
public:
	CacheThread();
	virtual ~CacheThread();
	void run() ; //继承线程的函数
	void add_cache(CacheQuery *p_cache);  //通过接口来注册到线程中
private:
	void process();
	std::vector<CacheQuery *> _p_cache_vec ;

};

#endif /* CACHETHREAD_H_ */

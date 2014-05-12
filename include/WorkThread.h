/*
 * WorkThread.h
 *
 *  Created on: Apr 23, 2014
 *      Author: wang
 */

#ifndef WORKTHREAD_H_
#define WORKTHREAD_H_
#include <pthread.h>
#include <string.h>
#include <string>
#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <map>
#include <vector>
#include <unistd.h>
#include "Thread.h"
#include "EncodingConverter.h"
#include "CacheQuery.h"
class ThreadPool ;
class Task ;

class WorkThread :public Thread{
public:
	WorkThread();
	void run() ; //线程所要完成的任务
	void work_task(Task &task); //计算的任务
	void register_thread_pool(ThreadPool *p_thread_pool) ;  //用于注册线程池，使线程可以从此线程池中取得任务
	CacheQuery *get_cache_query();      //返回对象的一个指针

private:
	ThreadPool *_p_thread_pool ;
	int m_socket_fd ;
	CacheQuery _cachequery ;



};

#endif /* WORKTHREAD_H_ */

/*
 * ThreadPool.h
 *
 *  Created on: Apr 23, 2014
 *      Author: wang
 */

#ifndef THREADPOOL_H_
#define THREADPOOL_H_
#include <queue>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "WorkThread.h"
#include "MutexLock.h"
#include "Condition.h"
#include "noncopyable.h"
#include "Task.h"
class ThreadPool :public noncopyable{
public:
	ThreadPool(std::vector<WorkThread>::size_type max_thread);
	virtual ~ThreadPool();

	void start_thread_pool() ;    // let the thread pool work
	void stop_thread_pool() ;      // stop the thread pool

	bool add_task_queue(Task task) ;  // add the task
	bool get_task_queue(Task &task) ;  // get a task to deal with

	bool is_task_queue_empty() const  ;  // whether there are tasks
	std::queue<Task>::size_type get_task_queue_size() const ; // get the size of task queue


private:
	std::queue<Task> _task_queue ; //task queue, 任务队列
	std::vector<WorkThread>::size_type _max_thread ; //the number of thread， 线程的最大数目
	std::vector<WorkThread> _thread_vector ;   // thread vector //线程数组

	bool _is_started ; //the signal of thread pool
	mutable MutexLock _lock ;   // mutex
	mutable Condition _cond ;    //cond

	//应该将字典类作为线程词的唯一对象
};

#endif /* THREADPOOL_H_ */

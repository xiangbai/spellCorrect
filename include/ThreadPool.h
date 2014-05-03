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
struct Task{
	std::string req_buf;   //
	struct sockaddr_in m_clinet_addr ;
};
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
	std::queue<Task> _task_queue ; //task queue
	std::vector<WorkThread>::size_type _max_thread ; //the number of thread
	std::vector<WorkThread> _thread_vector ;   // thread vector

	bool _is_started ; //the signal of thread pool
	mutable MutexLock _lock ;   // mutex
	mutable Condition _cond ;    //cond
};

#endif /* THREADPOOL_H_ */

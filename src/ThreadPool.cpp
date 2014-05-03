/*
 * ThreadPool.cpp
 *
 *  Created on: Apr 23, 2014
 *      Author: wang
 */

#include "ThreadPool.h"
#include <iostream>
//once init thread pool , start the thread to work
ThreadPool::ThreadPool(std::vector<WorkThread>::size_type max_thread)
:_task_queue() , _max_thread(max_thread),  _thread_vector(_max_thread) ,
 _is_started(false) , _lock() , _cond(&_lock){
	// TODO Auto-generated constructor stub
	for(std::vector<WorkThread>::iterator iter = _thread_vector.begin() ; iter != _thread_vector.end() ; ++iter)
	{
		iter->register_thread_pool(this) ;
	}
}

ThreadPool::~ThreadPool() {
	// TODO Auto-generated destructor stub
	stop_thread_pool() ;
}


void ThreadPool::start_thread_pool() {
	if(_is_started == false)
	{
		//start work thread working ;
		_is_started = true ;
		for(std::vector<WorkThread>::iterator iter = _thread_vector.begin() ; iter != _thread_vector.end() ; ++iter)
		{
			iter->start();
		}
	}
}
void ThreadPool::stop_thread_pool() {
	if(_is_started == false)
	{
		return ;
	}
	_is_started = false ;
	_cond.notifyAll() ;
	if(!is_task_queue_empty())
	{
		_task_queue.pop() ;
	}
}

bool ThreadPool::add_task_queue(Task task){
	GuardLock temp(&_lock) ;
	bool ret = false ;
	if(_is_started)
	{
		std::cout<<"add task queue "<<task.req_buf<<std::endl;
		_task_queue.push(task);
		_cond.notify();   //notify work pthread there are tasks
		ret = true ;
	}
	return ret ;
}
bool ThreadPool::get_task_queue(Task &task){
	GuardLock temp(&_lock) ;
	//if the task queue is empty , wait
	while(_is_started && _task_queue.empty())   //这里调用队列自身的empty，否则造成死锁
	{
		_cond.wait();
	}
	//if the thread pool is false , return
	if(_is_started == false)
	{
		_cond.notifyAll();
		return false ;
	}

	//get the task from task queue
	task = _task_queue.front();
	_task_queue.pop() ;
	return true ;
}

bool ThreadPool::is_task_queue_empty() const{
	GuardLock temp(&_lock) ;
	bool ret = false ;
	ret = _task_queue.empty() ;
	return ret ;
}
std::queue<Task>::size_type ThreadPool::get_task_queue_size() const {
	GuardLock temp(&_lock) ;
	std::vector<WorkThread>::size_type ret = _task_queue.size() ;
	return ret ;
}



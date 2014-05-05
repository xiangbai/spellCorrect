/*
 * WorkThread.cpp
 *
 *  Created on: Apr 23, 2014
 *      Author: wang
 */
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "WorkThread.h"
#include "ThreadPool.h"
WorkThread::WorkThread():_p_thread_pool(NULL){
	m_socket_fd = socket(AF_INET , SOCK_DGRAM , 0) ;

}
void WorkThread::run(){
	while(true)
	{
		Task task ;
		bool ret = _p_thread_pool->get_task_queue(task) ;  //获取查询词
		if(ret == false)
		{
			return ;
		}
		else
		{
			std::cout<<"get task : "<< task.req_buf << " deal with  " ;
			work_task(task) ;  //任务执行查询
		}
	}
	std::cout<<"end working"<<std::endl;
}
void WorkThread::work_task(Task &task){

	//std::size_t freq = task.p_sepllingCorrect->run_query(task.req_buf);
	//std::cout<<"frequence: "<<freq<<std::endl;
	std::size_t freq = 100;
	sendto(m_socket_fd, &freq, sizeof(std::size_t), 0,(struct sockaddr *)&(task.m_clinet_addr) , sizeof(task.m_clinet_addr)) ;
}

void WorkThread::register_thread_pool(ThreadPool *p_thread_pool){
		_p_thread_pool = p_thread_pool ;
}

/*
 * WorkThread.cpp
 *
 *  Created on: Apr 23, 2014
 *      Author: wang
 */
#include <iostream>
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
		bool ret = _p_thread_pool->get_task_queue(task) ;
		if(ret == false)
			return ;
		std::cout<<"get task : "<< task.req_buf << " deal with  " ;
		int result = compute_task(task.req_buf) ;
		sendto(m_socket_fd, &result, sizeof(float), 0,(struct sockaddr *)&(task.m_clinet_addr) , sizeof(task.m_clinet_addr)) ;
	}
	std::cout<<"end working"<<std::endl;
}
int WorkThread::compute_task(std::string buf){
	char op ;
	int operate1;
	int operate2 ;
	int result = 0;

	sscanf(buf.c_str() , "%d%c%d",&operate1 , &op , &operate2) ;
	switch(op)
	{
	case '+' :
		result = operate1 + operate2 ;
		break;
	case '-' :
		result = operate1 - operate2 ;
		break;
	case '*' :
		result = operate1 * operate2 ;
		break;
	case '/' :
		if(operate2==0)
		{
			throw std::runtime_error("divide cannot be zero");
		}
		result = operate1 / operate2 ;
		break;
	}
	return result ;
}
void WorkThread::register_thread_pool(ThreadPool *p_thread_pool){
		_p_thread_pool = p_thread_pool ;
}

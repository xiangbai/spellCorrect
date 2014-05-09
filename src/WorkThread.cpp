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
#include "Dictionary.h"
#include "Task.h"
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
			std::cout<<"get task : "<< task.req_buf << " deal with  " <<std::endl;
			work_task(task) ;  //任务执行查询, 完成查询池与字典词库的距离计算
		}
	}
	std::cout<<"end working"<<std::endl;
}
void WorkThread::work_task(Task &task){

	/*
	 * 获取的搜索词可能会是汉字，此时该如何去处理？
	 */
	//在这里定义一个字典类
	Dictionary *p_dictionary = Dictionary::get_instance(); //获取独一的一份字典
	std::string result  = task.runing_query(task.req_buf, p_dictionary->get_map()) ; //执行搜索匹配操作
	EncodingConverter trans ;
	result = trans.gbkToutf8(result) ;
	std::cout<<"runing query result is "<<result<<std::endl;

	//返回纠错信息给客户端
	std::size_t len = sendto(m_socket_fd, result.c_str(), result.size(), 0,(struct sockaddr *)&(task.m_clinet_addr) , sizeof(task.m_clinet_addr)) ;

}
void WorkThread::register_thread_pool(ThreadPool *p_thread_pool){
		_p_thread_pool = p_thread_pool ;
}

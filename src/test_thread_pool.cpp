/*
 * test_thread_pool.cpp
 *
 *  Created on: Apr 23, 2014
 *      Author: wang
 */
#include "ThreadPool.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
int main(int argc , char **argv)
{
	ThreadPool p(10) ;

	p.start_thread_pool() ;

	while(true)
	{
		Task task ;
		std::string word ;
		std::cin>>word ;
		task.req_buf = word ;
		p.add_task_queue(task) ;
		sleep(1);
	}
}





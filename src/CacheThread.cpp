/*
 * CacheThread.cpp
 *
 *  Created on: May 11, 2014
 *      Author: wang
 */

#include "CacheThread.h"

CacheThread::CacheThread(std::size_t interval):_interval(interval) {
	// TODO Auto-generated constructor stub

}
void CacheThread::run()
{
	while(true)
	{
		sleep(_interval);
		process();  //cache线程所要完车的任务
	}
}
void CacheThread::process()
{
	CacheQuery cache_query ;
	cache_query.write_into_cache() ;  //更新磁盘文件
}
CacheThread::~CacheThread() {
	// TODO Auto-generated destructor stub
}


/*
 * CacheThread.cpp
 *
 *  Created on: May 11, 2014
 *      Author: wang
 */

#include "CacheThread.h"
#include "CacheQuery.h"

CacheThread::CacheThread(){
	// TODO Auto-generated constructor stub

}
void CacheThread::run()
{
	while(true)
	{
		sleep(2);
		process();  //cache线程所要完成的任务
	}
}
void CacheThread::process()
{
	//CacheQuery cache_query ;
	//cache_query.write_into_cache() ;  //更新磁盘文件
	for(std::vector<CacheQuery *>::iterator iter = _p_cache_vec.begin() ; iter != _p_cache_vec.end() ; ++iter)
	{
		CacheQuery *p_cache = *iter ;    //分别读取cache查询类，更新磁盘
		p_cache->write_into_cache();
	}
}
void CacheThread::add_cache(CacheQuery *p_cache)
{
	_p_cache_vec.push_back(p_cache) ;   //将工作线程中的cache注册到cache线程中
}
CacheThread::~CacheThread() {
	// TODO Auto-generated destructor stub
}


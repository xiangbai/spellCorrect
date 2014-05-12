/*
 * Task.h
 *
 *  Created on: May 6, 2014
 *      Author: wang
 */

#ifndef TASK_H_
#define TASK_H_

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "StringUtil.h"
#include "Query.h"
#include "EncodingConverter.h"
class CacheQuery ;
class Dictionary ;
class Task {
public:
	Task();
	virtual ~Task();
	std::string req_buf;   //查询词
	struct sockaddr_in m_clinet_addr ;  //客户端端口号
	//在字典中查询搜索词,同时接收cache缓存中的内容
	std::string runing_query(std::string &search, Dictionary *p_dictionary, CacheQuery &p_cachequery);
	void create_set(std::string &search, std::set<std::size_t>&set_search, Dictionary *p_dictionary);

	std::string cache_query(std::string &search, CacheQuery &p_cachequery);
};

#endif /* TASK_H_ */

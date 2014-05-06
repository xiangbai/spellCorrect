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
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "StringUtil.h"
#include "Query.h"
class Task {
public:
	Task();
	virtual ~Task();
	std::string req_buf;   //查询词
	struct sockaddr_in m_clinet_addr ;  //客户端端口号
	//在字典中查询搜索词
	const std::string run_query(const std::string &search, const std::map<std::string, std::size_t> &map_dic)const;
};

#endif /* TASK_H_ */

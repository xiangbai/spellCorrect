/*
 * Server.h
 *
 *  Created on: Apr 25, 2014
 *      Author: wang
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <fstream>
#include <stdlib.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/select.h>
#include <stdexcept>
#include <map>
#include "Task.h"
#define MAXFD 64
typedef int SOCKET ;
class ThreadPool ;
class Server {
public:
	Server(const std::string &ip , const std::string &port, const std::string &dictionary);   //create socket , bind server
	virtual ~Server();  //close socket
	void start(ThreadPool *p);  //启动监听
	int sent_message(const void *buf , size_t len);
	int recv_message(void *buf , size_t len) ;
	const struct sockaddr_in get_client_addr()const;   //为线程池提供客户端信息
	const SOCKET get_socket_fd()const;
private:
	SOCKET _socket_fd ;
	socklen_t m_len ;
	struct sockaddr_in m_server_addr ;   //the info of server
	struct sockaddr_in m_client_addr ;   // the info of client
};

#endif /* SERVER_H_ */

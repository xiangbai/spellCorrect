/*
 * Server.cpp
 *
 *  Created on: Apr 25, 2014
 *      Author: wang
 */

#include "Server.h"

Server::Server(std::string &ip , std::string &port):_socket_fd(0) {
	// TODO Auto-generated constructor stub
	//socket
	if(-1 == (_socket_fd = socket(AF_INET , SOCK_DGRAM , 0))){
		throw std::runtime_error("socket");
	}
	memset(&m_server_addr , 0  , sizeof(m_server_addr)) ;
	memset(&m_client_addr , 0 , sizeof(m_client_addr)) ;

	m_server_addr.sin_family = AF_INET ;
	m_server_addr.sin_port = htons(atoi(port.c_str())) ;
	m_server_addr.sin_addr.s_addr = inet_addr(ip.c_str()) ;
	//bind server
	if(-1 == bind(_socket_fd , (struct sockaddr *)&m_server_addr , sizeof(m_server_addr)))
	{
		throw std::runtime_error("bind") ;
	}
	m_len = sizeof(m_client_addr) ;
}
//发送数据出去
int Server::sent_message(const void *buf , size_t len){
	return sendto(_socket_fd, buf, len, 0, (struct sockaddr *)&m_client_addr , sizeof(m_client_addr)) ;
}
//接收从客户端发送过来的任务
int Server::recv_message(void *buf , size_t len){
	return recvfrom(_socket_fd, buf, len, 0, (struct sockaddr *)&m_client_addr, &m_len) ;
}
//供外界获取客户端信息
const struct sockaddr_in Server::get_client_addr()const
{
	return m_client_addr ;
}
//用于服务器监听客户请求
const SOCKET Server::get_socket_fd()const
{
	return _socket_fd;
}
Server::~Server() {
	// TODO Auto-generated destructor stub
	close(_socket_fd);
}


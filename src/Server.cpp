/*
 * Server.cpp
 *
 *  Created on: Apr 25, 2014
 *      Author: wang
 */

#include "Server.h"
#include "ThreadPool.h"
#include "StringUtil.h"

Server::Server(const std::string &ip , const std::string &port, const std::string &dictionary):_socket_fd(0) {
	// TODO Auto-generated constructor stub
	//socket
	if(-1 == (_socket_fd = socket(AF_INET , SOCK_DGRAM , 0))){
		throw std::runtime_error("socket");
	}
	memset(&m_server_addr , 0  , sizeof(m_server_addr)) ;
	memset(&m_client_addr , 0 , sizeof(m_client_addr)) ;
	//需要重置端口号
	//设置端口号重用
	bool bReuseaddr=true;
	setsockopt(_socket_fd,SOL_SOCKET,SO_REUSEADDR,(char*)&bReuseaddr,sizeof(bool));

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

//服务器开始监听客户端发送过来的消息
void Server::start(ThreadPool *p)
{
	StringUtil string_util ;
	//监听设置
	fd_set fd_rd, fd_rd_back;
	struct timeval tm;
	int socket_fd = _socket_fd;
	FD_SET(socket_fd, &fd_rd);
	tm.tv_sec = 1;
	tm.tv_usec = 0 ;

	std::string recv ;
	char recv_buf[1024];

	while(true)
	{
		memset(recv_buf, 0, 1024);
		fd_rd_back = fd_rd;
		select(1024, &fd_rd_back, NULL, NULL, &tm);
		//监听到客户端发送过来的请求
		if(FD_ISSET(socket_fd, &fd_rd_back))
		{
			Task task ;
			this->recv_message((void *)recv_buf , sizeof(recv_buf));   //接收客户端发送过来的任务消息
			//trim(recv_buf);   //处理受到的字符
			recv = recv_buf;
			string_util.upperTolower(recv);
			std::cout<<"recv informa : "<<recv<<std::endl;

			task.m_clinet_addr=m_client_addr;   //获取客户端的ip地址和port号
			task.req_buf = recv ;   //客户端发送过来的命令请求

			p->add_task_queue(task) ;   //线程池将任务添加到任务队列中，有工作线程来执行任务
			sleep(1);
		}
	}
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


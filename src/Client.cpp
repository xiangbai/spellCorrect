/*
 * Client.cpp
 *
 *  Created on: Apr 25, 2014
 *      Author: wang
 */

#include "Client.h"

Client::Client(std::string &ip , std::string &port) {
	// TODO Auto-generated constructor stub
	m_socket_fd = socket(AF_INET , SOCK_DGRAM , 0);
	if(m_socket_fd == -1)
	{
		throw std::runtime_error("socket");
	}
	memset(&m_server_addr , 0 , sizeof(m_server_addr)) ;
	m_server_addr.sin_family = AF_INET ;
	m_server_addr.sin_port = htons(atoi(port.c_str())) ;
	m_server_addr.sin_addr.s_addr = inet_addr(ip.c_str()) ;
	m_len = sizeof(m_server_addr);
}
int Client::send_message(const void *buf , size_t len)
{
	return sendto(m_socket_fd, buf, len, 0, (struct sockaddr *)&m_server_addr , sizeof(m_server_addr)) ;
}
int Client::recv_message(void *buf , size_t len)
{
	return recvfrom(m_socket_fd, buf, len, 0,NULL, NULL) ;
}
Client::~Client() {
	// TODO Auto-generated destructor stub
	close(m_socket_fd);
}



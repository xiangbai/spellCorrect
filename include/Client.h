/*
 * Client.h
 *
 *  Created on: Apr 25, 2014
 *      Author: wang
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdexcept>
class Client {
public:
	Client(std::string &ip , std::string &port);
	int send_message(const void *buf , size_t len);
	int recv_message(void *buf , size_t len);
	virtual ~Client();
private:
	int m_socket_fd ;
	struct sockaddr_in m_server_addr ;
	int m_len ;
};

#endif /* CLIENT_H_ */

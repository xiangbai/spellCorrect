#include <iostream>
#include "Client.h"
int main(int argc , char **argv)
{
/*	int server_fd = socket(AF_INET, SOCK_DGRAM ,  0 );
	if(server_fd == -1)
	{
		throw std::runtime_error("socket");
	}
	struct sockaddr_in server_addr ;
	server_addr.sin_family = AF_INET ;
	server_addr.sin_port = htons(6688);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int result ;
	socklen_t len = sizeof(server_addr) ;
	std::string word ;
	while(std::cin >> word)
	{
		int iret =sendto(server_fd, word.c_str(),word.size(), 0, (struct sockaddr*)&server_addr, 16);
		recvfrom(server_fd, &result, 4, 0, NULL, NULL);
		std::cout <<"result: " << result << std::endl ;
	}*/
	std::string ip("127.0.0.1");
	std::string port("6688");
	Client client(ip, port);
	int result = 0;
	std::string word ;
	while(std::cin>>word){
		int iret = client.send_message((void *)word.c_str(), word.size());
		client.recv_message((void*)&result, 4);
		std::cout<<"result: "<<result<<std::endl;
	}
	return 0 ;
}

#include <iostream>
#include <fstream>

#include "Server.h"
#include "ThreadPool.h"
#include "Conf.h"
//守护进程
void Daemon()
{
	int i=3;
	if(fork()!= 0)
	{
		exit(0);
	}
	setsid();
	chdir("/");
	umask(0);
	for(; i< MAXFD; ++i)
	{
		 close(i);
	}
}
void trim(std::string &word)  //转换大小写字母，去除标点符号
{
	char word_buf[128];
		strcpy(word_buf, word.c_str());
		int i = 0,j = 0 ;
		while(i != word.size())
		{
			if(!ispunct(word[i]))  //去除标点符号
			{
				if(isupper(word[i]))  //大写字母转换成小写字母
				{
					word_buf[j++] = tolower(word[i]);
				}
				else
				{
					word_buf[j++] = word[i] ;
				}
			}
			i++;
		}
		word = word_buf;
}
int main(int argc , char **argv)
{
	/****************守护进程begin***************/
	//Daemon();
	/****************守护进程end***************/

    Conf conf("server");  //读取服务器的文件配置
	std::string ip, port;
	std::string dictionary ;
	ip = conf.get_value("ServerIp");  //获取IP
	port=conf.get_value("ServerPort");  // 获取port
	dictionary=conf.get_value("Dictionary");   //获取字典
	Server server(ip , port, dictionary) ;  //连接服务器，并开启服务器


	ThreadPool p(10) ;    //创建线程池
	p.start_thread_pool() ;   //启动线程，这时所有的线程都已经启动

	server.start(&p);   //启动服务器开始监听客户端发送的消息
	return 0 ;
}

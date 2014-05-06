/*
 * Conf.cpp
 *
 *  Created on: May 4, 2014
 *      Author: wang
 */

#include "Conf.h"

Conf::Conf(std::string dir) {
	// TODO Auto-generated constructor stub
	if(dir == "server")      //服务器路径
	{
		s_filename = FILEDIR ;
	}
	else if(dir == "thesaurus")   //词库路径
	{
		s_filename = WORDDIR ;
	}
	else if(dir == "stopwords")   //停用词路径
	{
		s_filename = STOPDIR;
	}
	else if(dir == "dictionary")
	{
		s_filename = DICTIONDIR ;  //字典文件的路径
	}
	std::ifstream fin(s_filename.c_str());
	if(!fin)
	{
		throw std::runtime_error("file open failed");
	}
	std::string key , value;
	while(fin >> key >> value)   //打开配置文件，读取里面相应的文件信息
	{
		m_read.insert(make_pair(key, value));
	}
}

const std::string Conf::get_value(const std::string &key)const
{
	std::map<std::string, std::string>::const_iterator it = m_read.find(key);
	if(it == m_read.end())
	{
		throw std::runtime_error("error read configure file");
	}

	return it->second;
}
Conf::~Conf() {
	// TODO Auto-generated destructor stub
}


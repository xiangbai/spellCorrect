/*
 * Dictionary.cpp
 *
 *  Created on: May 6, 2014
 *      Author: wang
 */

#include "Dictionary.h"

MutexLock Dictionary::_lock;
Dictionary *Dictionary::_p_dictionary = NULL ;

Dictionary *Dictionary::get_instance()
{
	if(_p_dictionary == NULL)
	{
		_lock.lock();
		if(_p_dictionary == NULL)
		{
			_p_dictionary = new Dictionary;
		}
		_lock.unlock();
	}
	return _p_dictionary ;
}
//服务器创建自己的词库map,以供线程进行查询
void Dictionary::create_dictionary(const std::string &filename, std::map<std::string, std::size_t> &direction)
{
	std::ifstream fin;
	fin.open(filename.c_str());
	if(!fin)
	{
		throw std::runtime_error("file open failed");
	}
	std::string word;
	std::size_t count;
	while(fin >> word >>count)   //构成词库
	{
		//统计单词的词频，去除重复词的存储
		std::pair<std::map<std::string, std::size_t>::iterator, bool> ret =
				m_direction.insert(std::make_pair(word, 1));
		if (!ret.second)
		{
			++ret.first->second;
		}
	}
}
//返回词库
const std::map<std::string, std::size_t> Dictionary::get_map()const
{
	return m_direction ;
}
Dictionary::~Dictionary() {
	// TODO Auto-generated destructor stub
	delete _p_dictionary ;
}


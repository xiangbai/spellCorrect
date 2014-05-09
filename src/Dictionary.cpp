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
void Dictionary::create_dictionary(const std::string &filename)
{
	std::ifstream fin;
	fin.open(filename.c_str());
	if(!fin)
	{
		throw std::runtime_error("file open failed");
	}
	std::string word;
	std::size_t count;
	std::pair<std::string, std::size_t> word_count ;
	std::size_t index = 0 ;
	std::size_t cur_index = 0 ;
	while(fin >> word >>count)   //构成词库
	{
		//统计单词的词频，去除重复词的存储
		/*std::pair<std::map<std::string, std::size_t>::iterator, bool> ret =
				m_direction.insert(std::make_pair(word, 1));
		if (!ret.second)
		{
			++ret.first->second;
		}*/
		word_count = make_pair(word, count);
		_word_vec.push_back(word_count);  //得到词，词频数组
		cur_index = index++ ;
		std::string temp = word_count.first ;
		create_index(temp, cur_index);  // 建立索引
	}
}
//为每一个词建立一个索引
void Dictionary::create_index(std::string &word, std::size_t index)
{
	EncodingConverter trans ;
	StringUtil string_util ;
	word = trans.utf8Togbk(word) ;
	int i ;
	unsigned char a ;

	//读取每个字节
	for(i = 0; i != word.size(); ++i)
	{
		a = word[i] ;
		if(a & 0x80)  //结果是等于128，表示是汉字
		{
			unsigned char str_= (unsigned char)word[i] ;
			unsigned char str_add = (unsigned char)word[++i] ;

			uint16_t temp = str_<< 8 | str_add ;  //只是一个字节的uint16_t的值
			//可能会有重复词的存在
			iter->first = temp ;
			iter->second.insert(index) ;

		}
		else  //结果小于128， 表示为ASCII
		{
			iter->first = (uint16_t)(unsigned char) word[i] ;
			iter->second.insert(index) ;

		}
		++iter ;
	}

}
//返回词库

Dictionary::~Dictionary() {
	// TODO Auto-generated destructor stub
	delete _p_dictionary ;
}


/*
 * Dictionary.h
 *
 *  Created on: May 6, 2014
 *      Author: wang
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <string.h>
#include "MutexLock.h"
#include "CreateDictionary.h"
#include "EncodingConverter.h"
#include "StringUtil.h"
#include "Conf.h"
/*
 * 单例模式的类，将其构造函数定义为private， 只允许初始化一次
 * 在初始化该类的同时就为字典建立一个索引，提高查询速度
 */
class Dictionary {
public:
	virtual ~Dictionary();
	static Dictionary *get_instance();  //定义返回该实例的一个对象指针

	std::vector<std::pair<std::string, std::size_t> > _word_vec ;  //采用下表直接可以得到相应词组及其词频

	std::map<std::string, std::set<std::size_t> > m_word ;  //词，映射到该词所在的vector数组，也就是索引
private:
	Dictionary()
    {
		Conf conf("dictionary");
		std::string filename = conf.get_value("FileName") ;
		_word_vec.clear();
		m_word.clear();
	   //创建服务器自己的词库
		create_dictionary(filename);  //保存的有自己的词库，但这只保留的是英文词库
    }

	static MutexLock _lock;
	static Dictionary *_p_dictionary;

	//std::map<std::string, std::size_t> m_direction ;  //服务器的字典词库

	void create_dictionary(const std::string &filename);
	void create_index(std::string &word, std::size_t index);




};

#endif /* DICTIONARY_H_ */

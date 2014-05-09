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
#include <string.h>
#include "MutexLock.h"
#include "CreateDictionary.h"
#include "Conf.h"
/*
 * 单例模式的类，将其构造函数定义为private， 只允许初始化一次
 */
class Dictionary {
public:
	virtual ~Dictionary();
	static Dictionary *get_instance();  //定义返回该实例的一个对象指针
	const std::map<std::string, std::size_t> &get_map() ;
private:
	Dictionary()
    {
		m_direction.clear();
		Conf conf("dictionary");
		std::string filename = conf.get_value("FileName") ;

	   //创建服务器自己的词库
		create_dictionary(filename, m_direction);  //保存的有自己的词库，但这只保留的是英文词库
    }

	static MutexLock _lock;
	static Dictionary *_p_dictionary;
	std::map<std::string, std::size_t> m_direction ;  //服务器的字典词库

	void create_dictionary(const std::string &filename, std::map<std::string, std::size_t> &direction);
};

#endif /* DICTIONARY_H_ */

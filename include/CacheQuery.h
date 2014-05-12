/*
 * CacheQuery.h
 *
 *  Created on: May 10, 2014
 *      Author: wang
 */

#ifndef CACHEQUERY_H_
#define CACHEQUERY_H_


#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <set>
#include <map>
#include <hash_map>
#include <vector>
#include <stdexcept>
#include "Conf.h"
#include "MutexLock.h"
/*
 * 使用cache是为了记录查询记录，将部分信息直接存储在内存中，这样就不用每次都在索引表中查找
 * 有个文件记录搜索的结果，格式如：搜索词	结果返回值
 * 考虑要定期的更新cache中的内容
 * 有个状态值来记录cache是否改变过
 * 添加查询结果到cache文件中
 * 从hash_map中查找相应的搜索结果值，并将该值返回回去。
 * 刚开始使用这个cache时，cache文件中是空的?如果是空的则在索引表中进行查询
 * 也不能说是一直无限的写入到该cache文件中？更新又是什么时候
 */
namespace __gnu_cxx {
template<> struct hash<std::string> {
	std::size_t operator()(const std::string &s) const {
		hash<const char *> h;
		return h(s.c_str());
	}
};
}
class CacheQuery{
public:

	CacheQuery();
	virtual ~CacheQuery();
	/*
	 * 需要通过文件来存储部分信息到磁盘中，同时hash_map有更新的时候，需要将内容重新写入到磁盘中
	 * 注意对文件的读写需要考虑互斥的情况
	 * 需要考虑一个问题就是，这个cache是共享的还是每一个线程各自保存一个
	 */
	void read_from_cache();   //从磁盘中读入内容到cache中
	void write_into_cache();  //将cache中的hash_map写入到文件中

	void add_search_to_cache(std::pair<std::string, std::string> pair_set); //将搜索词和返回值添加到cache中
	void add_search_to_cache(const std::string &key, const std::string &value);  //重载添加词到cache函数

	void replace_key_in_cache(const std::string &key, const std::string &value);  //进行替换
	bool delete_key_in_cache(const std::string &key);   //删除不经常访问的键值对

	std::string get_value_in_cache(const std::string &key) ;  //通过键，返回值
	std::size_t get_size_of_hash_map()const;
private:
	__gnu_cxx ::hash_map<std::string, std::string, __gnu_cxx ::hash<std::string> > hash_search; //用于记录已经查询过的词的记录
	typedef __gnu_cxx ::hash_map<std::string, std::string, __gnu_cxx ::hash<std::string> >::iterator hash_search_iter ;
	typedef __gnu_cxx ::hash_map<std::string, std::string, __gnu_cxx ::hash<std::string> >::const_iterator hash_search_iter_const ;
	bool is_cache_update ;
	std::string _filename ;
	MutexLock _lock ;
};

#endif /* CACHEQUERY_H_ */

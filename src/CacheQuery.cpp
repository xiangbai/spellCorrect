/*
 * CacheQuery.cpp
 *
 *  Created on: May 10, 2014
 *      Author: wang
 */

#include "CacheQuery.h"
#include <fstream>
/*
 * g++ CacheQuery.cpp -I../include -Wno-deprecated 编译方式
 */

/*
 * 有一个问题就是我的cache线程开启要执行的任务就是要扫描磁盘，定期的更新hash_map和磁盘上面的内容
 */
CacheQuery::CacheQuery():is_cache_update(false) {
	// TODO Auto-generated constructor stub
	Conf conf("cache");
	//read_from_cache(conf.get_value("CacheFilename"));    //将文件中的内容读入到cache中
	_filename = conf.get_value("CacheFilename");


}
/*
 * 读取内容到cache中
 */
void CacheQuery::read_from_cache()
{
	std::ifstream fin;
	fin.open(_filename.c_str());
	if(!fin)
	{
		throw std::runtime_error("file open failed");
	}
	std::string key, value ;
	std::string line ;
	while(std::getline(fin, line))    //从文件中读取出键和值，然后讲键和值读出到hash_map中。
	{
		std::istringstream stream(line);
		while(stream >> key>>value)
		{
			add_search_to_cache(key, value) ;
		}
		stream.clear();
	}
}
/*
 * 将hash_map中的内容写入到磁盘中，只有当hasp_map有新内容时就执行写操作
 */
void CacheQuery::write_into_cache()
{
	if(is_cache_update == false)  //未修改过则不写入磁盘
	{
		return ;
	}
	std::ofstream fout ;
	fout.open(_filename.c_str());
	if(!fout)
	{
		throw std::runtime_error("file open failed");
	}
	hash_search_iter_const iter = hash_search.begin() ;
	while(iter != hash_search.end())  //将hash_map写入到文件中
	{
		fout<<iter->first<<"\t"<<iter->second <<std::endl;
		++iter ;
	}
	fout.close();
	fout.clear();
	is_cache_update = false ;
	std::cout<<"更新到磁盘中"<<std::endl;

}
void CacheQuery::add_search_to_cache(std::pair<std::string, std::string> pair_set)
{
	//hash_search.insert(pair_set);   //将搜索词和查询词放入hash_map中
	add_search_to_cache(pair_set.first, pair_set.second);
}
void CacheQuery::add_search_to_cache(const std::string &key, const std::string &value)
{
	if(key == "" || value == "")
	{
		std::cout<<"the parameter is null"<<std::endl;
		return ;
	}
	std::pair <hash_search_iter, bool> ret = hash_search.insert(std::make_pair(key, value)); //将键值对添加到map中

	if(ret.second == false)  //插入失败,表明里面已经存在这样的键值对了
	{
		replace_key_in_cache(key, value);        //则执行替换，替换的规则需要自己来设定
	}
	else   //插入成功
	{
		is_cache_update = true ;  //表示hash_map修改过了
	}
}
//将相应的键值进行替换
void CacheQuery::replace_key_in_cache(const std::string &key, const std::string &value)
{
	if(key == "" || value == "")
	{
		std::cout<<"the parameter is null"<<std::endl;
		return ;
	}
	hash_search[key] = value ;   //hash_map已更新
	is_cache_update  = true ;
}
//将相应的键值对删除
bool CacheQuery::delete_key_in_cache(const std::string &key)
{
	hash_search_iter iter = hash_search.find(key) ;
	if(iter != hash_search.end())
	{
		hash_search.erase(key);
		is_cache_update = true ;
		return true ;
	}
	else
	{
		return false ;
	}

}
std::string CacheQuery::get_value_in_cache(const std::string &key)const   //外部可以通过键，直接返回值
{
	hash_search_iter_const iter = hash_search.find(key);
	if(iter  != hash_search.end())  //在cache中找到搜索词所对应的查询结果
	{
		return iter->second ;
	}
	else
	{
		return "" ;
	}
}
//获取hash_map的容量大小
std::size_t CacheQuery::get_size_of_hash_map()const
{
	return hash_search.size() ;
}


CacheQuery::~CacheQuery() {
	// TODO Auto-generated destructor stub
}

int main(int argc, char **argv)
{
	CacheQuery cache_query ;
	std::cout<<"before size if "<<cache_query.get_size_of_hash_map()<<std::endl;
	cache_query.add_search_to_cache(make_pair(std::string("hello"), std::string("nihao")));
	std::cout<<"get query: "<<cache_query.get_value_in_cache("hello")<<std::endl;
	std::cout<<"before size if "<<cache_query.get_size_of_hash_map()<<std::endl;
	return 0 ;
}

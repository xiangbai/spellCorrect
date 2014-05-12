/*
 * Task.cpp
 *
 *  Created on: May 6, 2014
 *      Author: wang
 */

#include "Task.h"
#include "Dictionary.h"
#include "CacheQuery.h"
Task::Task() {
	// TODO Auto-generated constructor stub
}

//进行搜索查询,这个主要用在对ASCII的搜索匹配
/*
 * 直接使用字典类中的词典索引
 */
void Task::create_set(std::string &search, std::set<std::size_t>&set_search, Dictionary *p_dictionary)
{
	std::cout<<"enter create_set, search is: "<<search<<std::endl;
	int i = 0 ;
	unsigned char a ;
	std::string temp ;
	EncodingConverter trans ;
	search = trans.utf8Togbk(search) ;
	for(i = 0; i != search.size(); ++i)
	{
		a =search[i] ;
		if(a & 0x80)  //结果是等于128，表示是汉字
		{
			std::string str_(1, search[i]) ;
			std::string str_add (1, search[++i]) ;
			temp = str_+ str_add ;  //只是一个字节的uint16_t的值

		}
		else  //结果小于128， 表示为ASCII
		{
			std::string temp1(1,search[i]);
			temp = temp1 ;
		}
	//	std::cout<<"temp: "<<trans.gbkToutf8(temp)<<std::endl ;
		 //解析出字符的所有索引下标
		//std::cout<<"get each word size: "<<p_dictionary->m_word[temp].size()<<std::endl;

		for(std::set<std::size_t>::iterator iter = p_dictionary->m_word[temp].begin(); iter != p_dictionary->m_word[temp].end(); ++iter)
		{
			set_search.insert(*iter);  //不重复的将搜索词的下标加入到搜索集合中
		}
	}
	std::cout<<"set_search size is "<<set_search.size()<<std::endl;      //获取搜索集合的大小
}
//直接查询字典中的索引
std::string Task::runing_query(std::string &search, Dictionary *p_dictionary, CacheQuery &p_cachequery)
{

	EncodingConverter trans ;
	std::cout<<"get search: "<<search<<std::endl;   //获取搜索词，每个搜索词都有一个set集合，需要对这些集合进行合并，从这些合并集中计算数据的编辑距离
	std::vector<Query> query_vec ;  //查询集合数组
	StringUtil string_util ;
	/*
	 * 先在cache缓存中查询
	 */
	std::string result = cache_query(search, p_cachequery);

	if(result.size() != 0)  //表示成功的返回查询结果
	{
		return result ;
	}
     //在cache缓存中查找失败才会去内存的索引中查询
	/*
	 * 需要对搜索词进行分解
	 */
	std::set<std::size_t> set_search ;
	/*
	 * 现在已经获得合并集合了所有下标，则直接在我的这个合并集合中计算其编辑距离
	 */
	std::string search_temp = search ;

	create_set(search_temp, set_search, p_dictionary); //在字典索引中创建搜索集合


	//在索引合并集合中计算编辑距离
	std::set<std::size_t>::iterator set_iter ;
	for(set_iter = set_search.begin(); set_iter != set_search.end(); ++set_iter)
	{
		Query query ;
		std::string word = p_dictionary->_word_vec[*set_iter].first;
		query.set_word(word) ;  //获取词
		query.set_count(p_dictionary->_word_vec[*set_iter].second); //获取词频
		std::string first = word ;  //里面都是GBK格式的
		query.set_edit_dis(string_util.edit_distance(search, trans.gbkToutf8(first)));

		if(query.get_edit_dis() < 2)
		{
			query_vec.push_back(query);
		}
	}
	//排序规则
	Query query ;
	query.sort_query(query_vec);  //按照编辑距离从小到大排序
	//std::cout<<"top is "<<query_vec[0].get_word()<<std::endl;
	std::cout<<"top edit_dis is: "<<query_vec[0].get_edit_dis()<<std::endl;
	std::cout<<"top word is: "<<trans.gbkToutf8(query_vec[0].get_word())<<std::endl;

	p_cachequery.add_search_to_cache(search,query_vec[0].get_word()) ;  //添加到cache缓存中

	return query_vec[0].get_word() ;   //返回类型为GBK
}
std::string Task::cache_query(std::string &search, CacheQuery &p_cachequery)
{
	std::cout<<"enter cache_query"<<std::endl;
	p_cachequery.read_from_cache() ;  //从磁盘读出内容到cache缓存中
	std::string result = p_cachequery.get_value_in_cache(search);  //直接从cache缓存中得到结果

	std::cout<<"the size of result is "<<result.size()<<std::endl;
	return result ;
}





Task::~Task() {
	// TODO Auto-generated destructor stub
}

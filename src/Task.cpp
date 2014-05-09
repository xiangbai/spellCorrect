/*
 * Task.cpp
 *
 *  Created on: May 6, 2014
 *      Author: wang
 */

#include "Task.h"

Task::Task() {
	// TODO Auto-generated constructor stub

}
//进行搜索查询,这个主要用在对ASCII的搜索匹配
std::string Task::runing_query(std::string &search, const std::map<std::string, std::size_t>  &map_dic)
{

	std::cout<<"get search: "<<search<<std::endl;
	std::cout<<"get size "<<map_dic.size()<<std::endl;

	std::vector<Query> query_vec ;  //查询集合数组

	StringUtil string_util ;

	std::map<std::string, std::size_t>::const_iterator map_it = map_dic.begin();

	while(map_it != map_dic.end())
	{
			/*
			 * 每个词都要与搜素词进行计算最短编辑距离
			 * 这个效率是极其低下的，因为有一些词完全没有比较的必要性
			 */

		Query query;
		query.set_word(map_it->first);
		query.set_count(map_it->second) ;
		std::string first = map_it->first;
		query.set_edit_dis(string_util.edit_distance(search, first)) ;  //计算编辑距离

		if(query.get_edit_dis() < 3)
		{
			query_vec.push_back(query);
			std::cout<<query.get_word() << "  "<<query.get_count() << "  " <<query.get_edit_dis()<<std::endl;
		}
		++map_it ;
	}

	//排序规则
	Query query ;
	query.sort_query(query_vec);  //按照编辑距离从小到大排序
	return query_vec[0].get_word() ;
}
Task::~Task() {
	// TODO Auto-generated destructor stub
}

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
//进行搜索查询
const std::string Task::run_query(const std::string &search, const std::map<std::string, std::size_t> &map_dic)const
{
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
		query.set_edit_dis(string_util.edit_distance(search, map_it->first)) ;  //计算编辑距离



		if(query.get_edit_dis() < 3)
		{
			query_vec.push_back(query);
		}
		++map_it ;
	}
	//这种情况是返回了所有的查询结果，是无序情况
	for(std::vector<Query>::iterator iter = query_vec.begin() ; iter != query_vec.end() ; ++iter)
	{
		std::cout<<"word: "<<iter->get_word()<<"  frequency: "<<iter->get_count()<<"  edit distance: "<<iter->get_edit_dis()<<std::endl;
	}

	//排序规则
	Query query ;
	query.sort_query(query_vec);

	std::cout<<std::endl<<std::endl<<"after sort: "<<std::endl;

	for(std::vector<Query>::iterator iter = query_vec.begin() ; iter != query_vec.end() ; ++iter)
	{
		std::cout<<"word: "<<iter->get_word()<<"   frequency: "<<iter->get_count()<<"  edit distance: "<<iter->get_edit_dis()<<std::endl;
	}
	return query_vec[0].get_word();
}
Task::~Task() {
	// TODO Auto-generated destructor stub
}


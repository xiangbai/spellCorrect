/*
 * CreateIndex.cpp
 *
 *  Created on: May 9, 2014
 *      Author: wang
 */

#include "CreateIndex.h"
#include <iostream>


void CreateIndex::create_index(const std::string &search, const std::map<std::string, std::size_t>  &map_dic)
{
	int i = 0 ;
	std::set<uint16_t> char_s ;  //有序存储
	//std::pair<std::map<std::string, std::size_t >::iterator, std::map<std::string, std::size_t >::iterator > ret;
	std::map<std::string, std::size_t>::const_iterator iter = map_dic.begin();
	for(; i != search.size(); ++i)
	{
		char_s.insert(search[i]);
		// map_dic.equal_range() ;
	}
}
CreateIndex::~CreateIndex() {
	// TODO Auto-generated destructor stub
}


int main(int argc, char **argv)
{
	std::string search("nooe");

	std::map<std::string, std::size_t> map_dic ;  //字典
	map_dic.insert(std::pair<std::string, std::size_t>("nooek", 12));
	map_dic.insert(std::pair<std::string, std::size_t>("keel", 12));
	map_dic.insert(std::pair<std::string, std::size_t>("noke", 12));
	map_dic.insert(std::pair<std::string, std::size_t>("else", 12));
	map_dic.insert(std::pair<std::string, std::size_t>("ok", 12));

	std::map<std::set<char>, std::set<std::string> > m_word_index ;    //索引

	std::map<std::set<char>, std::set<std::string> >::iterator iter = m_word_index.begin();

	std::pair<std::map<std::string, std::size_t>::iterator , std::map<std::string, std::size_t>::iterator > ret ;
	std::set<char> char_s ;

	for(int i = 0; i < search.size(); ++i)
	{
		std::string temp = search[i];
		char_s.insert(search[i]);   //每个字符的存储
		ret = map_dic.equal_range(temp);
		iter->second.insert(ret.first->first);
		++iter ;

	}

	iter = m_word_index.begin();
	for(; iter != m_word_index.end(); ++iter)
	{
	   for(std::set<std::string>::iterator itv = iter->second.begin(); itv != iter->second.end(); ++itv)
	   {
	         std::cout<<"  "<<*itv<<"  " ;
	   }
	   std::cout<<std::endl;
	}


	for(std::set<char>::iterator iter = char_s.begin(); iter != char_s.end(); ++iter)
	{
		std::cout<<*iter<<std::endl;
	}


	return 0;
}

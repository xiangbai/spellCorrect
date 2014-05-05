/*
 * SpellingCorrect.cpp
 *
 *  Created on: May 4, 2014
 *      Author: wang
 */

#include "SpellingCorrect.h"


//用于运行查询的结果
const std::string SpellingCorrect::run_query(const std::string &word)
{
	std::vector<Query> query_vec ;  //查询集合数组

	StringUtil string_util ;

	std::map<std::string, std::size_t>::const_iterator map_it = _words_count.begin();

	std::priority_queue<Query, std::vector<Query>, compare > q;

	while(map_it != _words_count.end())
	{
		/*
		 * 每个词都要与搜素词进行计算最短编辑距离
		 * 这个效率是极其低下的，因为有一些词完全没有比较的必要性
		 */
		Query query;

		query.set_word(map_it->first);
		query.set_count(map_it->second) ;
		query.set_edit_dis(string_util.edit_distance(word, map_it->first)) ;

		//std::cout<<"edit distance is "<< string_util.edit_distance(word, map_it->first) <<std::endl;

		if(query.get_edit_dis() <= 3)
		{
			//std::cout<<"in the if "<<std::endl;
			query_vec.push_back(query);
			q.push(query);   //优先级队列
		}
		++map_it ;
	}
	Query temp = q.top();
	std::cout<<"run_queue "<<temp.get_word() << "共有"<<temp.get_count()<<std::endl;
	return temp.get_word() ;

}
//文件的打开
static std::ifstream &open_file(std::ifstream &in, const std::string &file_name)
{
	in.close();
	in.clear();
	in.open(file_name.c_str());
	return in;
}
static void handing_text(std::string &line, std::vector<std::string> &words, std::map<std::string, std::size_t> &word_count)  //文本处理，将大写转换成小写，去除标点符号
{
	std::string word ;
	StringUtil string_util ;  //调用StringUtil类，完成对字符的大小写转换，去除标点符号，计算最短编辑距离
	std::istringstream sin(line);
	while(sin >> word)   //构成词库
	{
		string_util.upperTolower(word);
		words.push_back(word);
		//统计单词的词频，去除不重复词的存储
		std::pair<std::map<std::string, std::size_t>::iterator, bool> ret =
						word_count.insert(std::make_pair(word, 1));
		if (!ret.second)
		{
			++ret.first->second;
		}
	}
	sin.clear();

}
void SpellingCorrect::read_file()  // read file
{
	Conf conf("thesaurus");   //配置文件类
	std::ifstream in ;
	if(!open_file(in, conf.get_value("FileName")))  //打开文件
	{
		throw std::runtime_error("open file failed");
	}
	std::string line;

	/*
	 * 讲结果写入到Map中，以构成词库的形式 key \t value
	 */
	while(std::getline(in, line))    //按行读取文件内容
	{
		handing_text(line, _words, _words_count);  //处理单词
	}
	in.close();
}
SpellingCorrect::~SpellingCorrect() {
	// TODO Auto-generated destructor stub
}


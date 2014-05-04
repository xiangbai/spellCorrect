/*
 * SpellingCorrect.cpp
 *
 *  Created on: May 4, 2014
 *      Author: wang
 */

#include "SpellingCorrect.h"

SpellingCorrect::SpellingCorrect() {
	// TODO Auto-generated constructor stub
	_words.clear();
	_stop_word.clear();
	_words_count.clear();
}
//文件的打开
static std::ifstream &open_file(std::ifstream &in, const std::string &file_name)
{
	in.close();
	in.clear();
	in.open(file_name.c_str());
	return in;
}
static void trim(std::string &word)
{
	char word_buf[128];
	strcpy(word_buf, word.c_str());
	int i = 0,j = 0 ;
	while(i != word.size())
	{
		if(ispunct(word[i]))  //去除标点符号
		{
			if(isupper(word[i]))  //大写字母转换成小写字母
			{
				word_buf[j++] = tolower(word[i]);
			}
			else
			{
				word_buf[j++] = word[i] ;
			}
		}
		i++;
	}
	word = word_buf;
}

static void handing_text(std::string &line, std::vector<std::string> &words, std::map<std::string, std::size_t> &word_count)  //文本处理，将大写转换成小写，去除标点符号
{
	std::string word ;
	std::istringstream sin(line);
	while(sin >> word)   //构成词库
	{
		trim(word);
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


	while(std::getline(in, line))    //按行读取文件内容
	{
		handing_text(line, _words, _words_count);  //处理单词
	}
	in.close();
}
SpellingCorrect::~SpellingCorrect() {
	// TODO Auto-generated destructor stub
}


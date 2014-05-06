/*
 * CreateDictionary.cpp
 *
 *  Created on: May 6, 2014
 *      Author: wang
 */

#include "CreateDictionary.h"

CreateDictionary::CreateDictionary(const std::string &source, const std::string &destion){
	// TODO Auto-generated constructor stub
	read_file(source);  //读取原文件和字典文件
	write_file(destion);
}

CreateDictionary::~CreateDictionary() {
	// TODO Auto-generated destructor stub
}
//文件的打开
static std::ifstream &open_file(std::ifstream &in, const std::string &file_name)
{
	in.close();
	in.clear();
	in.open(file_name.c_str());
	return in;
}
static void handing_text(std::string &line, std::map<std::string, std::size_t> &word_count)  //文本处理，将大写转换成小写，去除标点符号
{
	std::string word ;
	std::istringstream sin(line);
	StringUtil stringutil ;
	while(sin >> word)   //构成词库
	{
		stringutil.upperTolower(word);  //大写转小写，去除标点符号
		//统计单词的词频，去除重复词的存储
		std::pair<std::map<std::string, std::size_t>::iterator, bool> ret =
						word_count.insert(std::make_pair(word, 1));
		if (!ret.second)
		{
			++ret.first->second;
		}
	}
	sin.clear();
}
void CreateDictionary::read_file(const std::string &source)
{
	std::ifstream in ;

	if(!open_file(in, source))  //打开文件
	{
		throw std::runtime_error("open file failed");
	}
	std::string line;

		/*
		 * 讲结果写入到Map中，以构成词库的形式 key \t value
		 */
	while(std::getline(in, line))    //按行读取文件内容
	{
		handing_text(line, _words_count);  //处理单词
	}


	in.close();
}
//写入到字典文件中
void CreateDictionary::write_file(const std::string &destion)
{
	std::ofstream fout ;
	fout.open(destion.c_str());
	if(!fout)
	{
		throw std::runtime_error("file open failed");
	}
	std::map<std::string, std::size_t>::const_iterator iter = _words_count.begin();
	while(iter != _words_count.end())
	{
		fout<<iter->first <<"\t"<<iter->second<<std::endl;
		++iter ;
	}
}

int main(int argc, char **argv)
{
	std::string source("/var/www/spellCorrect/data/big.txt");
	std::string destion("/var/www/spellCorrect/data/dictionary.txt");
	CreateDictionary dictionary(source, destion);
	return 0 ;
}


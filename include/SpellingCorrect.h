/*
 * SpellingCorrect.h
 *
 *  Created on: May 4, 2014
 *      Author: wang
 */

#ifndef SPELLINGCORRECT_H_
#define SPELLINGCORRECT_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <vector>
#include <stdexcept>
#include <map>
#include <set>
#include <queue>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Conf.h"
#include "StringUtil.h"
#include "Query.h"
/*
 * 文本纠错类，读取词集，形成自己的词库，完成对查询词的纠正任务
 */
struct compare{
	bool operator()(const Query &a, const Query &b){
		return a < b;
	}
};
class SpellingCorrect {
public:
	SpellingCorrect(){
		// TODO Auto-generated constructor stub
		_words.clear();
		_stop_word.clear();
		_words_count.clear();
		read_file(); //读取文件词集
	}

	const std::string run_query(const std::string &word);


	virtual ~SpellingCorrect();
private:
	std::vector<std::string> _words;  //词集
	std::map<std::string, std::size_t> _words_count ;  //词频
	std::set<char> _stop_word ; //停用词


	void read_file();  //读文件，以保存词集


};

#endif /* SPELLINGCORRECT_H_ */

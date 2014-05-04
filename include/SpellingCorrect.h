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
#include <ctype.h>
#include <vector>
#include <stdexcept>
#include <map>
#include <set>
#include "Conf.h"
class SpellingCorrect {
public:
	SpellingCorrect();
	virtual ~SpellingCorrect();
private:
	std::vector<std::string> _words;  //词集
	std::map<std::string, std::size_t> _words_count ;  //词频
	std::set<char> _stop_word ; //停用词

	void read_file();  //读文件，以保存词集
};

#endif /* SPELLINGCORRECT_H_ */

/*
 * CreateDictionary.h
 *
 *  Created on: May 6, 2014
 *      Author: wang
 */

/*
 * 创建字典类，用于更新服务器上面的词库字典
 */
#ifndef CREATEDICTIONARY_H_
#define CREATEDICTIONARY_H_
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string.h>
#include <stdexcept>
#include "StringUtil.h"

class CreateDictionary {
public:
	CreateDictionary(const std::string &source, const std::string &destion);
	virtual ~CreateDictionary();
private:
	std::map<std::string, std::size_t> _words_count;
	void read_file(const std::string &source);
	void write_file(const std::string &destion);
};

#endif /* CREATEDICTIONARY_H_ */

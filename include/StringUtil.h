/*
 * StringUtil.h
 *
 *  Created on: May 5, 2014
 *      Author: wang
 */

#ifndef STRINGUTIL_H_
#define STRINGUTIL_H_

#include <iostream>
#include <string>
#include <string.h>
#include <ctype.h>
class StringUtil {
public:
	StringUtil();
	virtual ~StringUtil();
	std::size_t edit_distance(const std::string &str1, const std::string &str2); //计算两个字符的最小编辑距离
	void upperTolower(std::string & word); //将大写转换成小写
//	void ignore_punct(std::string &word);  //忽略标点符号
private:
	int min(int a, int b)
	{
		return a < b ? a : b ;
	}
};

#endif /* STRINGUTIL_H_ */

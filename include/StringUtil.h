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
#include <stdint.h>
#include <vector>
#include "EncodingConverter.h"
class StringUtil {
public:
	StringUtil();
	virtual ~StringUtil();
	void upperTolower(std::string & word); //将大写转换成小写

	void toUint16_t(std::string &str, std::vector<uint16_t> &uint_t);   //将字符串转换存储到uint16_t数组中

	std::size_t edit_distance(const std::string &str1, const std::string &str2); //计算两个字符的最小编辑距离

private:
	std::size_t edit(const std::vector<uint16_t> &str1, const std::vector<uint16_t> &str2);  //通用类型的计算最短编辑距离

	int min(int a, int b)
	{
		return a < b ? a : b ;
	}
};

#endif /* STRINGUTIL_H_ */

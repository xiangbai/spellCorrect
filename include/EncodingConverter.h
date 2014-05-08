/*
 * EncodingConverter.h
 *
 *  Created on: May 7, 2014
 *      Author: wang
 */

#ifndef ENCODINGCONVERTER_H_
#define ENCODINGCONVERTER_H_

#include <iconv.h>
#include <string>
#include <stdlib.h>
#include <stdexcept>
#include <string.h>
#include <cstring>

class EncodingConverter {
public:
	EncodingConverter();
	virtual ~EncodingConverter();
	std::string  utf8Togbk(const std::string &s);
	std::string gbkToutf8(const std::string &s);
private:
	//调用库函数iconv.h中的函数进行转换
	int code_convert(const char *from_charset, const char *to_charset, char *inbuf, int inlen, char *outbuf, int outlen);
};

#endif /* ENCODINGCONVERTER_H_ */

/*
 * EncodingConverter.cpp
 *
 *  Created on: May 7, 2014
 *      Author: wang
 */

#include "EncodingConverter.h"
#include <iostream>

const std::size_t MAX_LEN = 256 ;

EncodingConverter::EncodingConverter() {
	// TODO Auto-generated constructor stub

}

EncodingConverter::~EncodingConverter() {
	// TODO Auto-generated destructor stub
}


std::string EncodingConverter::utf8Togbk(const std::string &s)
{
	char *inbuf = new char[s.size() + 1] ;
	strcpy(inbuf, s.c_str());    // utf code
	char *outbuf = new char[MAX_LEN] ;
	int inlen = strlen(inbuf) ;
	int outlen = MAX_LEN ;
	code_convert("utf-8", "gb2312",inbuf, inlen, outbuf, outlen);
	std::string conver_s(outbuf);
	delete [] inbuf;
	delete [] outbuf;
	return conver_s ;
}
std::string EncodingConverter::gbkToutf8(const std::string &s)
{
	char *inbuf = new char[s.size() + 1] ;
	strcpy(inbuf, s.c_str());    // utf code
	char *outbuf = new char[MAX_LEN] ;
	int inlen = strlen(inbuf) ;
	int outlen = MAX_LEN ;
	code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, outlen);
	std::string conver_s(outbuf);
	delete [] inbuf;
	delete [] outbuf;
	return conver_s ;
}
int EncodingConverter::code_convert(const char *from_charset, const char *to_charset, char *inbuf, int inlen, char *outbuf, int outlen)
{
	iconv_t cd;
	char **pin = &inbuf;
	char **pout = &outbuf;
	cd = iconv_open(to_charset, from_charset);
	if(cd == 0)
	{
		return -1 ;
	}
	memset(outbuf, 0, outlen);

	iconv(cd, pin, (std::size_t *)&inlen, pout, (std::size_t *)&outlen);  //直接调用函数实现编码的转换

	iconv_close(cd);
	return 0 ;
}

/*int main(int argc, char **argv)
{
	EncodingConverter trans;
	std::string s = "王奶奶给刘奶奶倒牛奶";	// UTF8
	std::cout<<"before: "<<s<<std::endl;
	s = trans.utf8Togbk(s);	// UTF8 -> GBK
	s = trans.gbkToutf8(s);
	std::cout<<"after: "<<s<<std::endl;
	return 0 ;
}*/

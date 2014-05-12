/*
 * StringUtil.cpp
 *
 *  Created on: May 5, 2014
 *      Author: wang
 */

#include "StringUtil.h"

StringUtil::StringUtil() {
	// TODO Auto-generated constructor stub

}
StringUtil::~StringUtil() {
	// TODO Auto-generated destructor stub
}
void StringUtil::toUint16_t(std::string &str, std::vector<uint16_t> &uint_t)  //将ASCII和汉字统一转换存储格式为uint16_t
{
	int i ;
	unsigned char a ;
	for(i = 0; i != str.size(); ++i)
	{
		a = str[i] ;
		if(a & 0x80)  //结果是等于128，表示是汉字
		{
			unsigned char str_= (unsigned char)str[i] ;

			unsigned char str_add = (unsigned char)str[++i] ;

			uint16_t temp = str_<< 8 | str_add ;
			uint_t.push_back(temp) ;
		}
		else  //结果小于128， 表示为ASCII
		{
			uint_t.push_back((uint16_t)(unsigned char) str[i]) ;

		}
	}
/*	std::cout<<uint_t.size()<<std::endl;
	for(std::vector<uint16_t>::iterator iter = uint_t.begin(); iter != uint_t.end(); ++iter)
	{
		std::cout<<*iter<<std::endl;
	}*/
}

//外部调用计算最短编辑距离算法
std::size_t StringUtil::edit_distance(const std::string &str1, const std::string &str2)
{
	std::vector<uint16_t> u_str1,u_str2 ;
	std::string temp_str1 = str1 ;
	std::string temp_str2 = str2 ;
	EncodingConverter trans ;
	temp_str1 = trans.utf8Togbk(temp_str1) ;  //编码转换，将读进来的UTF-8转换成GBK格式处理
	temp_str2 = trans.utf8Togbk(temp_str2) ;

	toUint16_t(temp_str1, u_str1); //将数据存储在uint16_t的数组中
	toUint16_t(temp_str2, u_str2);

	return edit(u_str1, u_str2);
}

//通用版本的计算最短编辑距离
std::size_t StringUtil::edit(const std::vector<uint16_t> &str1, const std::vector<uint16_t> &str2)
{
	std::size_t m = str1.size();
	std::size_t n = str2.size();

	int **d ;
	d = new int*[m+1];
	for(int i = 0 ; i <= m ; ++i)
	{
		d[i] = new int[n+1] ;
	}
	d[0][0] = 0 ;
	int i , j ;
	for(i = 0 ; i <= m ; ++i)
	{
		d[i][0] = i ;
	}
	for (j = 0; j <= n; ++j)
	{
		d[0][j] = j ;
	}
	int temp = 0 ;


	for(i = 1 ; i<= m ; ++i)
	{
		for(j = 1 ; j <= n ; ++j)
		{
			if(str1[i-1] == str2[j-1])
			{
				temp = 0 ;
			}
			else
			{
				temp = 1 ;
			}
			d[i][j] = min(min(d[i-1][j] + 1 , d[i][j-1] + 1) , d[i-1][j-1]+temp) ; //编辑最短距离
		}
	}
	int result = d[m][n] ;
	for(int i = 0; i <= m; ++i)
	{
		delete [] d[i];
	}
	delete [] d ;
	return result ;
}

void StringUtil::upperTolower(std::string &word)
{
	char word_buf[128];
		strcpy(word_buf, word.c_str());
		int i = 0,j = 0 ;
		while(i != word.size())
		{
			if(!ispunct(word[i]))  //去除标点符号
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
			++i;
		}
		word_buf[j] = '\0';  //注意字符数组必须要以'\0'结尾
		word = word_buf;
}

/*int main(int argc, char **argv)
{
	StringUtil string_util ;
	std::string str1("鸡汤");
	std::string str2("o");

	std::string str3("ok");
	std::string str4("okd");
	std::size_t edit = string_util.edit_distance(str1, str2) ;
	std::cout<<edit<<std::endl;
	return 0 ;
}*/

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

std::size_t StringUtil::edit_distance(const std::string &str1, const std::string &str2)
{
	std::size_t m = str1.size();
	std::size_t n = str2.size();
	int **d ;
	int temp = 0 ;
	d = new int*[m+1];
	for(int i = 0 ; i <= m ; ++i)
	{
		d[i] = new int[n+1] ;
	}
	d[0][0] = 0 ;
	int i , j ;
	for(i = 1 ; i <= m ; ++i)
	{
		d[i][0] = i ;
	}
	for (j = 1; j <= n; ++j)
	{
		d[0][j] = j ;
	}
	for(i = 1 ; i<= m ; ++i)
	{
		for(j = 1 ; j <= n ; ++j)
		{
			if(str1[i] == str2[j])
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
	return d[m][n] ;
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
			i++;
		}
		word = word_buf;
}

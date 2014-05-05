/*
 * Query.h
 *
 *  Created on: May 5, 2014
 *      Author: wang
 */

#ifndef QUERY_H_
#define QUERY_H_

#include <iostream>
#include <string>
#include <map>
/*
 * 查询结构体类
 */
class Query {
public:
	Query();
	virtual ~Query();

	void set_edit_dis(std::size_t distance);
	void set_word(std::string word);
	void set_count(std::size_t count);

	const std::string get_word()const ;
	const std::size_t get_count() const ;
	const std::size_t get_edit_dis() const;


	friend bool operator<(const Query &lhs, const Query &ths);
	friend bool operator>(const Query &lhs, const Query &ths);

private:
	std::string _word;  //词，频率
	std::size_t _count ;
	std::size_t _Edit_dis ;        //计算的最短编辑距离
};


//比较规则有问题
inline bool operator<(const Query &lhs, const Query &ths)
{
	if(lhs._Edit_dis == ths._Edit_dis)
		return lhs._count < ths._count ;
	else
		return lhs._Edit_dis < ths._Edit_dis ;
}

#endif /* QUERY_H_ */

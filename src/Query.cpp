/*
 * Query.cpp
 *
 *  Created on: May 5, 2014
 *      Author: wang
 */

#include "Query.h"

Query::Query():_count(0), _Edit_dis(0){
	// TODO Auto-generated constructor stub

}

Query::~Query() {
	// TODO Auto-generated destructor stub
}


void Query::set_word(std::string word){
	_word = word;
}
void Query::set_count(std::size_t count){
	_count = count ;
}

const std::string Query::get_word()const
{
	return _word;
}
const std::size_t Query::get_count() const {
	return _count ;
}
void Query::set_edit_dis(std::size_t distance)
{
	_Edit_dis = distance ;
}
const std::size_t Query::get_edit_dis() const
{
	return _Edit_dis ;
}

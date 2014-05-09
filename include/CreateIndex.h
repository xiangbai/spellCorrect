/*
 * CreateIndex.h
 *
 *  Created on: May 9, 2014
 *      Author: wang
 */

/*
 * 是为搜索词建立一个索引，以减少数据查询计算的范围
 */
#ifndef CREATEINDEX_H_
#define CREATEINDEX_H_

#include <map>
#include <set>
#include <vector>
#include <stdint.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

class CreateIndex {
public:
	CreateIndex(const std::string &search, const std::map<std::string, std::size_t>  &map_dic)
    {
		create_index(search, map_dic);
    }
	virtual ~CreateIndex();
private:
	std::map<std::set<uint16_t>, std::set<uint16_t> > m_word_index; //需要同时考虑ASCII和汉字的情况
	void create_index(const std::string &search, const std::map<std::string, std::size_t>  &map_dic);
};

#endif /* CREATEINDEX_H_ */

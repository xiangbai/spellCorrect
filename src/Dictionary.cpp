/*
 * Dictionary.cpp
 *
 *  Created on: May 6, 2014
 *      Author: wang
 */

#include "Dictionary.h"

MutexLock Dictionary::_lock;
Dictionary *Dictionary::_p_dictionary = NULL ;
/*
 * 索引建立成功，可以直接通过访问词来找到相应的词和词频
 */
Dictionary *Dictionary::get_instance()  //单例模式
{
	if(_p_dictionary == NULL)
	{
		_lock.lock();
		if(_p_dictionary == NULL)
		{
			_p_dictionary = new Dictionary;
		}
		_lock.unlock();
	}
	return _p_dictionary ;
}
//服务器创建自己的词库map,以供线程进行查询
void Dictionary::create_dictionary(const std::string &filename)
{
	std::ifstream fin;
	std::cout<<"filename is "<<filename<<std::endl;
	fin.open(filename.c_str());
	if(!fin)
	{
		throw std::runtime_error("file open failed");
	}
	std::string word;
	std::size_t count;
	std::string word_;
	std::size_t index = 0 ;
	while(fin >> word >>count>>word_)   //从字典中读出内容，构成词库
	{
		std::pair<std::string, std::size_t> word_count ;
		word_count = make_pair(word, count);
		_word_vec.push_back(word_count);  //得到词，词频数组
		std::string temp = word_count.first ;
		this->create_index(temp, index++);  // 建立索引,词对应该词在vector中的小标
	}
	std::cout<<"_word_vec size is "<<_word_vec.size()<<std::endl;
	fin.close();
}

//为每一个词建立一个索引，需要解析读出来的每一个词
void Dictionary::create_index(std::string &word, std::size_t index)
{
	/*
	 * 解析字符串中的每个词,为每个词建立索引
	 */
	EncodingConverter trans ;
	int i ;
	unsigned char a ;
	//读取每个字节
	for(i = 0; i != word.size(); ++i)
	{
		a =word[i] ;
		if(a & 0x80)  //结果是等于128，表示是汉字
		{
			std::string str_(1, word[i]) ;
			std::string str_add (1, word[++i]) ;
			std::string  temp ;
			temp = str_+ str_add ;  //只是一个字节的uint16_t的值
			//可能会有重复词的存在
			//temp = trans.gbkToutf8(temp) ;  //解析出每个单词
			m_word[temp].insert(index) ;  //使用下标的访问方式,temp采用存储GBK格式数据
		}
		else  //结果小于128， 表示为ASCII
		{
			std::string temp(1,word[i]);
			m_word[temp].insert(index) ;
		}
	}
}
//返回词库

Dictionary::~Dictionary() {
	// TODO Auto-generated destructor stub
	delete _p_dictionary ;
}


 //*测试main函数，可以成功的找到相应的词和词频
/*
int main(int argc, char **argv)
{
	Dictionary *p_dictionary = Dictionary::get_instance();
	EncodingConverter trans ;
	std::string temps("黑");
	temps = trans.utf8Togbk(temps) ;
	std::set<std::size_t> temp = p_dictionary->m_word[temps] ;
	for(std::set<std::size_t>::iterator iter = temp.begin(); iter != temp.end(); ++iter)
	{
		std::cout<< *iter <<"  ";   //获取该词的下标
		std::cout<<" "<<p_dictionary->_word_vec[*iter].first<<std::endl;
	}
	std::cout<<std::endl;
	std::cout<<temp.size()<<std::endl;
	return 0 ;
}
*/

/*
 * Conf.h
 *
 *  Created on: May 4, 2014
 *      Author: wang
 */

#ifndef CONF_H_
#define CONF_H_

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdexcept>
#include <string>
#include <map>
#define FILEDIR "/var/www/spellCorrect/conf/server.conf"
#define WORDDIR "/var/www/spellCorrect/conf/thesaurus.conf"
#define STOPDIR "/var/www/spellCorrect/conf/stop_word.conf"
class Conf {
public:
	Conf(std::string dir);
	const std::string get_value(const std::string &key)const;
	virtual ~Conf();
private:
	std::string s_filename ;
	std::map<std::string, std::string> m_read;
};

#endif /* CONF_H_ */

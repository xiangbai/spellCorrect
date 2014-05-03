#ifndef NONCOPYABLE_H_
#define NONCOPYABLE_H_
#include <iostream>
class noncopyable{
	protected:
		noncopyable(){
		}
		~noncopyable(){
		}
	private:
		noncopyable(const noncopyable &);
		noncopyable &operator=(const noncopyable &);
};
#endif

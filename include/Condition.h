#ifndef CONDITION_H_
#define CONDITION_H_
#include <iostream>
#include <pthread.h>
#include "MutexLock.h"

class Condition:public noncopyable{
	private:
		pthread_cond_t _cond ;
		MutexLock *_p_mutex ;
	public:
		Condition(MutexLock *p_mutex);
		~Condition() ;
		void wait() ;
		void notify() ;
		void notifyAll() ;
};
#endif

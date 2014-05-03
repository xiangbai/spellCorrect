#include "Condition.h"
//init condition
Condition::Condition(MutexLock *p_mutex):_p_mutex(p_mutex)
{
	pthread_cond_init(&_cond , NULL) ;
}
//destroy condition
Condition::~Condition()
{
	pthread_cond_destroy(&_cond) ;
}
// wait condition mutexlock
void Condition::wait(){
	pthread_cond_wait(&_cond , &(_p_mutex->_mutex)) ;
}
//notify a condition
void Condition::notify(){
	pthread_cond_signal(&_cond) ;
}
//notify all condition
void Condition::notifyAll(){
	pthread_cond_broadcast(&_cond) ;
}

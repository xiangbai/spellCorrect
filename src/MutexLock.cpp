#include "MutexLock.h"
#include "Condition.h"
//init lock
MutexLock::MutexLock()
{
	pthread_mutex_init(&_mutex , NULL) ;
}
//destroy lock
MutexLock::~MutexLock()
{
	pthread_mutex_destroy(&_mutex) ;
}
//lock 
void MutexLock::lock()
{
	pthread_mutex_lock(&_mutex);
}
//unlock
void MutexLock::unlock()
{
	pthread_mutex_unlock(&_mutex) ;
}

#ifndef MUTEXLOCK_H_
#define MUTEXLOCK_H_
#include <iostream>
#include <pthread.h>
#include "noncopyable.h"

class Condition ;
class MutexLock:public noncopyable{
	friend class Condition ;
	private:
		pthread_mutex_t _mutex ;
	public:
		MutexLock();
		~MutexLock();
		void lock();
		void unlock();
};
class GuardLock{
public:
	GuardLock(MutexLock *lock):_lock(lock){
		_lock->lock() ;
	}
	~GuardLock(){
		_lock->unlock();
	}
private:
	MutexLock *_lock ;
};
#endif

#include "Thread.h"
Thread::Thread():_pth(0){
	pthread_attr_init(&_attr);
}
Thread::~Thread() {
	pthread_attr_destroy(&_attr);
}

void Thread::start()
{
	pthread_attr_setdetachstate(&_attr , PTHREAD_CREATE_DETACHED);
	pthread_create(&_pth , &_attr , thread_handle , this);
}

void *Thread::thread_handle(void *arg)
{
	Thread *p = static_cast<Thread *>(arg) ;
	p->run() ;
	return NULL ;
}
pthread_t Thread::get_tid() const
{
	return _pth ;
}

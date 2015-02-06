#ifndef _TESTTHREAD_H_
#define _TESTTHREAD_H_

#include <pthread.h>
#define HELLO_WORLD_THREAD_NUM  20

class TestThread
{
public:
	TestThread();
	~TestThread();

	void initThread();

	int num[HELLO_WORLD_THREAD_NUM];
	
	static void *hello_world_thread(void *arg);

};

#endif _TESTTHREAD_H_
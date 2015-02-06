#include "TestThread.h"
#include <stdio.h>
#include <stdlib.h>

TestThread::TestThread()
{
	for (int i = 0; i < HELLO_WORLD_THREAD_NUM; i++)
	{
		num[i] = i;
	}
}


TestThread::~TestThread()
{
}

void TestThread::initThread()
{
	pthread_t threads[HELLO_WORLD_THREAD_NUM];
	int rc;
	int i;
	for (i = 0; i < HELLO_WORLD_THREAD_NUM; i++)
	{
		/**
		* @function int pthread_create(pthread_t * thread, const pthread_attr_t * attr, void * (*start_routine)(void *), void *arg)
		*     ���ո������߳�����attr����һ�����̣�process���ﴴ��һ���µ��̣߳�thread��
		* @param attr��
		*     ���attrΪNULL�����ڲ�ʹ��Ĭ�ϵ����Դ����̡߳�����ڴ����߳�֮���޸�attr���򲻻���Ѿ��������̲߳������á�
		* @param thread��
		*     �����̳߳ɹ��󣬽�thread id�洢��thread����ظ������ߡ�����thrad��ֵ��δ����ġ�
		* @param start_routine��
		*     �̴߳����ɹ��󣬿�ʼִ���̵߳���ں���start_routine��
		* @param arg��
		*     ������ͨ��argָ���߳���ں���start_routineר�õĲ���ָ�롣
		* @return ��
		*     0 �����ɹ�����0
		*     EAGAIN ������ϵͳ���ƣ��紴�����߳�̫�࣬һ��������ഴ���̸߳���PTHREAD_THREADS_MAX��
		*     EINVAL attr ��ֵ��Ч
		* @note pthread_create�����̺߳��߳���ں�������ʼִ�У�����Ҫ��ʾ����start_routine��ʼִ�С�
		*     ���ȷʵ��Ҫ���˹��̷�Ϊcreate��start2��������start_routine�Ժ�ִ�У�
		*     start_routine����ͨ���ȴ�һ������������condition variable������ͬ���ķ�ʽʵ�֡�
		*/

		rc = pthread_create(&threads[i], NULL, TestThread::hello_world_thread, &num[i]);
		if (rc)
		{
			printf("ERROR: pthread_create failed with %d\n", rc);
			return;
		}
	}


	for (i = 0; i<HELLO_WORLD_THREAD_NUM; i++)
	{
		/**
		* @function int pthread_join(pthread_t thread, void **status);
		*     �ȴ�thread�߳���ֹ
		*     ���threadָ�����̻߳�û����ֹ�������µ����̹߳���ֱ��threadָ�����߳���ֹΪֹ��
		* @param thread��
		*     ���ȴ��ĵ���ֹ�߳�
		* @param status��
		*     ���status��ֵ������NULL����ô����ֵ��ͨ��pthread_exit���ݹ����ġ�
		* @return ��
		*     0 �߳��Ѿ���ֹ
		*     ESRCH ����̲߳��ܵȴ�ͬһ���߳���ɣ��������һ���̻߳�ɹ���ɡ������߳̽���ֹ��������ESRCH ����
		*     EINVAL һ���ʾthread����Ч�Ĳ���
		*     EDEADLK ��鵽����״̬
		* @note
		*     ��������߳���δ���룬���߳�ID ��status ָ�����˳�״̬�����ֲ��䣬ֱ��Ӧ�ó������pthread_join() �Եȴ����̡߳�
		*     ���򣬽�����status���߳�ID �����������ա�
		*/
		//pthread_join(threads[i], NULL);
	}

	printf("INFO: All threads have been exit!!!\n");
}

void *TestThread::hello_world_thread(void *arg)
{
	int id = *((int*)arg);

	printf("pthread's Hello World!  %d\n" , id);
	/**
	* @function void pthread_exit(void *status)
	*     ��ֹ�������̣߳�
	* @param status��
	*     ͨ��status�����˳�״̬����pthread_join���ʹ��
	* @return ��
	*     �޷���ֵ��Ҳ�����ص�����÷���
	* @note
	*     ��������߳���δ���룬���߳�ID ��status ָ�����˳�״̬�����ֲ��䣬ֱ��Ӧ�ó������pthread_join() �Եȴ����̡߳�
	*     ���򣬽�����status���߳�ID �����������ա�
	*/
	pthread_exit(NULL);

	return NULL;
}

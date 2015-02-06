#ifndef _SOCKETMANAGER_H_
#define _SOCKETMANAGER_H_

#include "ODSocket.h"
#include <string>
#include "pthread.h"

using namespace std;

class SocketManager
{
public:
	SocketManager();
	~SocketManager();

	ODSocket odSocket;

	void connect(const string &ip, const unsigned short &port);

	string ip;
	unsigned short port;

private:

	//�����߳�
	pthread_t pConnetId;
	//����ͨ���߳�
	pthread_t pDataId;

	static void* connetting(void *arg);
	static void* receiveData(void *arg);

	void creatPonseThread();

};

#endif _SOCKETMANAGER_H_


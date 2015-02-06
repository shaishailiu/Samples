#include "SocketManager.h"
#include "log/LogTrace.h"
#include "utils/Memory.h"

SocketManager::SocketManager()
{
}


SocketManager::~SocketManager()
{
}

void SocketManager::connect(const string &ipAdress, const unsigned short &portAdress)
{
	ip = ipAdress;
	port = portAdress;

	int errCode = 0;
	
	pthread_attr_t tAttr;
	errCode = pthread_attr_init(&tAttr);
	errCode = pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);
	if (errCode != 0) {
		pthread_attr_destroy(&tAttr);
		return;
	}
	errCode = pthread_create(&pConnetId, &tAttr, connetting, this);
	
}

void* SocketManager::connetting(void *arg)
{
	SocketManager *manager = (SocketManager*)arg;
	ODSocket *odSocket = &(manager->odSocket);

	odSocket->Init();

	bool isok = odSocket->Create(AF_INET, SOCK_STREAM, 0);
	bool iscon = odSocket->Connect(manager->ip.c_str(), manager->port);
	if (iscon){
		trace("socket connet success!!");
		manager->creatPonseThread();
	}
	else{
		trace("socket connet fail!!");
	}
	return NULL;

}

void SocketManager::creatPonseThread()
{
	int errCode = 0;
	
	pthread_attr_t attributes;
	errCode = pthread_attr_init(&attributes);
	errCode = pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_DETACHED);
	if (errCode != 0) {
		pthread_attr_destroy(&attributes);
		return;
	}
	errCode = pthread_create(&pConnetId, &attributes, receiveData, this);
	

}

void* SocketManager::receiveData(void *arg)
{
	SocketManager *manager = (SocketManager*)arg;
	ODSocket *odSocket = &(manager->odSocket);
	while (true)
	{
		if (odSocket->Select() == -2){
			char recvBuf[2];// 获取请求头的 数据
			int i = odSocket->Recv(recvBuf, 2, 0);
			if (i==2)
			{
				short len = *(short*)&recvBuf[0];
				//memcpy(&len, &recvBuf[0], sizeof(short));

				char* messbody = new char[len];

				int j = odSocket->Recv(messbody, len, 0);

				short strLength;
				memcpy(&strLength, &messbody[0], sizeof(short));

				char *s = new char[strLength + 1];
				memcpy(s, &messbody[2], strLength);
				s[strLength] = 0;

				trace(s);
			}
		}
	}
	return NULL;
}



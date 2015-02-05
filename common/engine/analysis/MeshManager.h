#ifndef _MESHMANAGER_H_
#define _MESHMANAGER_H_

#include <string>
#include <map>
#include <vector>
#include <functional>

class MeshData;
class Display3dMovie;

using namespace std;

class MeshManager
{
public:
	MeshManager(void);
	~MeshManager(void);
	MeshData *getMesh(string fileUrl);
	//void loadMesh(string fileUrl,std::function<void (MeshData *)> func);
private:
	map<string,MeshData*> *meshDic;
	bool isInVector(vector<int> &vec,int id);
	int getIndexVector(vector<int> &vec,int id);
	bool hasCache(string &fileUrl);
};

#endif
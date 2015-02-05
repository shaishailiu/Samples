#ifndef _STATICMESHMANAGER_H_
#define _STATICMESHMANAGER_H_

#include <string>
#include <map>
#include <vector>
#include <functional>

class ObjData;

using namespace std;
class StaticMeshManager
{
public:
	StaticMeshManager();
	~StaticMeshManager();

	ObjData *getMesh(string fileUrl);

private:
	map<string, ObjData*> objDic;
};

#endif // !_STATICMESHMANAGER_H_

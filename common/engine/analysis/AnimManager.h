#ifndef _ANIMMANAGER_H_
#define _ANIMMANAGER_H_

#include <string>
#include <vector>
#include <map>

struct ObjectBone;
class AnimData;

using namespace std;

class AnimManager
{
public:
	AnimManager(void);
	~AnimManager(void);
	AnimData *getAnim(string fileUrl);
private:
	map<string,AnimData*> *animDic;
	vector<ObjectBone> frameToBone(vector<float> &frameData,vector<ObjectBone> &hierarchyList);
	void setFrameToMatrix(vector< vector<ObjectBone> > &frameAry);
	bool hasCache(string &fileUrl);
};

#endif


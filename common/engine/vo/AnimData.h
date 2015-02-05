#ifndef _ANIMDATA_H_
#define _ANIMDATA_H_

#include <vector>
#include "math/Matrix.h"
//class Matrix;
struct ObjectBone;

using namespace std;
class AnimData
{
public:
	AnimData(void);
	~AnimData(void);
	vector< vector<Matrix*> > &GetData();
	vector< vector<Matrix*> > *data;
	void setData(vector< vector<ObjectBone> > &animAry);
};

#endif


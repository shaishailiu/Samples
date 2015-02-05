#include "log/LogTrace.h"
#include "MeshVo.h"
#include "AnimData.h"


AnimData::AnimData(void)
{
	data = new vector<vector<Matrix*>>;
}


AnimData::~AnimData(void)
{
	for(int i=0;i<data->size();i++){
		vector<Matrix*> *maAry;
		maAry = &(*data)[i];

		for(int j=0;j<maAry->size();j++){
			delete (*maAry)[j];
		}
	}

	delete data;
}

void AnimData::setData( vector<vector<ObjectBone>> &animAry )
{
	for(int i=0;i<animAry.size();i++){
		vector<Matrix*> maAry;
		
		for(int j=0;j<animAry[i].size();j++){
			Matrix *ma = new Matrix(animAry[i][j].matrix);
			maAry.push_back(ma);
		}

		data->push_back(maAry);
	}
	//trace("ds");
}

vector<vector<Matrix*>> & AnimData::GetData()
{
	return *data;
}

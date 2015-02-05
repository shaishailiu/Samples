#include "MeshData.h"


MeshData::MeshData(void)
{
	boneNewIDAry = new vector<int>;
}


MeshData::~MeshData(void)
{
	delete boneNewIDAry;
}

void MeshData::setBoneNewIDAry( vector<int> &boneAry )
{
	//memcpy(boneNewIDAry,&boneAry[0],sizeof(int) * boneAry.size());
	for(int i=0;i<boneAry.size();i++){
		boneNewIDAry->push_back(boneAry[i]);
	}
}

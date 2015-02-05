#include <stdio.h>
#include <vector>
#include "vo/MeshVo.h"
#include "log/LogTrace.h"
#include "vo/MeshData.h"
#include "utils/Memory.h"
#include "utils/FileUtils.h"
#include <algorithm>
#include "MeshManager.h"
#include <GLES2/gl2.h>
#include <functional>

using namespace std;
MeshManager::MeshManager(void)
{
	meshDic = new map<string,MeshData*>;
}


MeshManager::~MeshManager(void)
{
}

MeshData *MeshManager::getMesh( string fileUrl )
{
	if(hasCache(fileUrl)){
		return (*meshDic)[fileUrl];
	}

	Memory *memory = FileUtils::loadFile(fileUrl.c_str());

	if(memory == NULL){
		return NULL;
	}

	//读取uv信息
	vector<ObjectUv> objuvList;
	int uvLength;
	//fread(&uvLength,sizeof(int),1,fp);
	memory->read(&uvLength,sizeof(int));
	for(int i=0;i<uvLength;i++){
		ObjectUv objuv;
		//fread(&objuv,sizeof(ObjectUv),1,fp);
		memory->read(&objuv,sizeof(ObjectUv));
		objuvList.push_back(objuv);
	}
	//读取index信息
	vector<ObjectTri> objtriList;
	vector<GLushort> indexAry;
	int triLength;
	//fread(&triLength,sizeof(int),1,fp);
	memory->read(&triLength,sizeof(int));
	for(int i=0;i<triLength;i++){
		ObjectTri objtri;
		//fread(&objtri,sizeof(ObjectTri),1,fp);
		memory->read(&objtri,sizeof(ObjectTri));
		objtriList.push_back(objtri);
		indexAry.push_back(objtri.t0);
		indexAry.push_back(objtri.t1);
		indexAry.push_back(objtri.t2);
	}
	//读取权重信息
	vector<ObjectWeight> objweightList;
	int weightLength;
	//fread(&weightLength,sizeof(int),1,fp);
	memory->read(&weightLength,sizeof(int));
	for(int i=0;i<weightLength;i++){
		ObjectWeight objweight;
		//fread(&objweight,sizeof(ObjectWeight),1,fp);
		memory->read(&objweight,sizeof(ObjectWeight));
		objweightList.push_back(objweight);
	}

	delete memory;

	/*
	FILE *fp;
	if((fp=fopen(fileUrl.c_str(),"rb"))==NULL){ 
		trace("can not find mesh file");
		return NULL;
	}
	
	//读取uv信息
	vector<ObjectUv> objuvList;
	int uvLength;
	fread(&uvLength,sizeof(int),1,fp);
	char *s;
	for(int i=0;i<uvLength;i++){
		ObjectUv objuv;
		fread(&objuv,sizeof(ObjectUv),1,fp);
		objuvList.push_back(objuv);
	}
	//读取index信息
	vector<ObjectTri> objtriList;
	vector<GLushort> indexAry;
	int triLength;
	fread(&triLength,sizeof(int),1,fp);
	for(int i=0;i<triLength;i++){
		ObjectTri objtri;
		fread(&objtri,sizeof(ObjectTri),1,fp);
		objtriList.push_back(objtri);
		indexAry.push_back(objtri.t0);
		indexAry.push_back(objtri.t1);
		indexAry.push_back(objtri.t2);
	}
	//读取权重信息
	vector<ObjectWeight> objweightList;
	int weightLength;
	fread(&weightLength,sizeof(int),1,fp);
	for(int i=0;i<weightLength;i++){
		ObjectWeight objweight;
		fread(&objweight,sizeof(ObjectWeight),1,fp);
		objweightList.push_back(objweight);
	}
	*/

	vector<int> boneUseAry;

	for(int i = 0;i<objuvList.size();i++){
		int beginIndex = objuvList[i].a;
		int allNum = objuvList[i].b;
		for(int skipNum = 0;skipNum<4;skipNum++){  
			int boneId;
			if(skipNum<allNum){
				//boneUseAry.push_back(objweightList[beginIndex+skipNum].boneId);
				boneId = objweightList[beginIndex+skipNum].boneId;
			}else{
				//boneUseAry.push_back(0);
				boneId = 0;
			}

			if(!isInVector(boneUseAry,boneId)){
				boneUseAry.push_back(boneId);
			}

		}
	}
	
	//trace("ds");

	vector<vector<GLfloat>> ary;
	vector<GLfloat> boneWeightAry;
	vector<GLfloat> uvArray;
	vector<GLfloat> boneIDAry;
	
	for(int i=0;i < 4;i++){
		vector<float> vbuff1;
		ary.push_back(vbuff1);
	}

	for(int i = 0;i<objuvList.size();i++){
		int beginIndex = objuvList[i].a;
		int allNum = objuvList[i].b;
		for(int skipNum = 0;skipNum<4;skipNum++){
			if(skipNum<allNum){
				ary[skipNum].push_back(objweightList[beginIndex+skipNum].x);
				ary[skipNum].push_back(objweightList[beginIndex+skipNum].y);
				ary[skipNum].push_back(objweightList[beginIndex+skipNum].z);
				boneIDAry.push_back(getIndexVector(boneUseAry,(objweightList[beginIndex+skipNum].boneId)));
				boneWeightAry.push_back(objweightList[beginIndex+skipNum].w); 
			}else{
				ary[skipNum].push_back(0);
				ary[skipNum].push_back(0);
				ary[skipNum].push_back(0);
				boneIDAry.push_back(0);
				boneWeightAry.push_back(0);
			}
		}
		uvArray.push_back(objuvList[i].x);
		uvArray.push_back(1-objuvList[i].y);
	}

	MeshData *meshData = new MeshData;

	//float *uvArray_a = new float [uvArray.size()] ;
	//memcpy(uvArray_a,&uvArray[0],sizeof(float) * uvArray.size());

	//vector<GLfloat> v0 = ary[0];
	//vector<GLfloat> v1 = ary[1];
	//vector<GLfloat> v2 = ary[2];
	//vector<GLfloat> v3 = ary[3];

	meshData->setBoneNewIDAry(boneUseAry);

	GLuint uvBuffer;
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvArray.size() * sizeof(GLfloat), (void *)&uvArray[0], GL_STATIC_DRAW);
	meshData->uvBuffer = uvBuffer;

	GLuint vertexBuffer1;
	glGenBuffers(1, &vertexBuffer1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer1);
	glBufferData(GL_ARRAY_BUFFER, ary[0].size() * sizeof(GLfloat), (void *)&ary[0][0], GL_STATIC_DRAW);
	meshData->vertexBuffer1 = vertexBuffer1; 

	GLuint vertexBuffer2;
	glGenBuffers(1, &vertexBuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer2);
	glBufferData(GL_ARRAY_BUFFER, ary[1].size() * sizeof(GLfloat), (void *)&ary[1][0], GL_STATIC_DRAW);
	meshData->vertexBuffer2 = vertexBuffer2;

	GLuint vertexBuffer3;
	glGenBuffers(1, &vertexBuffer3);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer3);
	glBufferData(GL_ARRAY_BUFFER, ary[2].size() * sizeof(GLfloat), (void *)&ary[2][0], GL_STATIC_DRAW);
	meshData->vertexBuffer3 = vertexBuffer3;

	GLuint vertexBuffer4;
	glGenBuffers(1, &vertexBuffer4);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer4);
	glBufferData(GL_ARRAY_BUFFER, ary[3].size() * sizeof(GLfloat), (void *)&ary[3][0], GL_STATIC_DRAW);
	meshData->vertexBuffer4 = vertexBuffer4;

	GLuint boneWeightBuffer;
	glGenBuffers(1, &boneWeightBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, boneWeightBuffer);
	glBufferData(GL_ARRAY_BUFFER, boneWeightAry.size() * sizeof(GLfloat), (void *)&boneWeightAry[0], GL_STATIC_DRAW);
	meshData->boneWeightBuffer = boneWeightBuffer;

	GLuint boneIdBuffer;
	glGenBuffers(1, &boneIdBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, boneIdBuffer);
	glBufferData(GL_ARRAY_BUFFER, boneIDAry.size() * sizeof(GLfloat), (void *)&boneIDAry[0], GL_STATIC_DRAW);
	meshData->boneIdBuffer = boneIdBuffer;

	GLuint IndexBuffer;
	glGenBuffers(1, &IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexAry.size() * sizeof(GLushort), (void *)&indexAry[0], GL_STATIC_DRAW);
	meshData->IndexBuffer = IndexBuffer;
	meshData->indexNum = indexAry.size();

	meshDic->insert(make_pair(fileUrl,meshData));

	return meshData;

	/*
	meshData.uvBuffer = this._context.createVertexBuffer(uvArray.length/2,2);
	meshData.uvBuffer.uploadFromVector(Vector.<Number>(uvArray),0,uvArray.length/2);

	meshData.vertexBuffer1 = this._context.createVertexBuffer(ary[0].length/3,3);
	meshData.vertexBuffer1.uploadFromVector(Vector.<Number>(ary[0]),0,ary[0].length/3);

	meshData.vertexBuffer2 = this._context.createVertexBuffer(ary[1].length/3,3);
	meshData.vertexBuffer2.uploadFromVector(Vector.<Number>(ary[1]),0,ary[1].length/3);

	meshData.vertexBuffer3 = this._context.createVertexBuffer(ary[2].length/3,3);
	meshData.vertexBuffer3.uploadFromVector(Vector.<Number>(ary[2]),0,ary[2].length/3);

	meshData.vertexBuffer4 = this._context.createVertexBuffer(ary[3].length/3,3);
	meshData.vertexBuffer4.uploadFromVector(Vector.<Number>(ary[3]),0,ary[3].length/3);

	meshData.boneWeightBuffer = this._context.createVertexBuffer(boneWeightAry.length/4,4);
	meshData.boneWeightBuffer.uploadFromVector(Vector.<Number>(boneWeightAry),0,boneWeightAry.length/4);

	meshData.boneIdBuffer = this._context.createVertexBuffer(bonetIDAry.length/4,4);
	meshData.boneIdBuffer.uploadFromVector(Vector.<Number>(bonetIDAry),0,bonetIDAry.length/4);

	meshData.indexBuffer = this._context.createIndexBuffer(indexAry.length);
	meshData.indexBuffer.uploadFromVector(Vector.<uint>(indexAry),0,indexAry.length);
	*/

}

bool MeshManager::isInVector(vector<int> &vec,int id){
	vector<int>::iterator result = find(vec.begin(),vec.end(), id ); //查找id
	if (result == vec.end()){
		return false;
	}else{ 
		return true;
	} 
}

int MeshManager::getIndexVector( vector<int> &vec,int id )
{
	for(GLint i=0;i<vec.size();i++){
		if(vec[i] == id){
			return i;
		}
	}
	return -1;
}

bool MeshManager::hasCache(string &fileUrl )
{
	map<string,MeshData*>::iterator it;
	it = meshDic->find(fileUrl);

	if(it == meshDic->end()){
		return false;
	}else {
		return true;
	}
}
/*
void MeshManager::loadMesh( string fileUrl,std::function<void (MeshData *)> func)
{
	MeshData *m = new MeshData;
	func(m);
}
*/


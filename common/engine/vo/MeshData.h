#ifndef _MESHDATA_H_
#define _MESHDATA_H_

#include <GLES2/gl2.h>
#include <vector>

using namespace std;
class MeshData
{
public:
	MeshData(void);
	~MeshData(void);
	GLuint uvBuffer;
	GLuint vertexBuffer1;
	GLuint vertexBuffer2;
	GLuint vertexBuffer3;
	GLuint vertexBuffer4;
	GLuint boneWeightBuffer;
	GLuint boneIdBuffer;
	GLuint IndexBuffer;
	int indexNum;
	vector<int> *boneNewIDAry;
	GLuint texture;
	void setBoneNewIDAry(vector<int> &boneAry);
};

#endif


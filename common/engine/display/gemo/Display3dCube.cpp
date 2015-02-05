#include "Engine.h"
#include "utils/Camera3D.h"
#include "utils/BindAttrib.h"
#include "vo/ObjData.h"
#include "math/Core.h"
#include "Display3dCube.h"

using namespace std;

Display3dCube::Display3dCube()
{
	initCubeData();
}


Display3dCube::~Display3dCube()
{
}

void Display3dCube::initCubeData()
{
	objData = new ObjData();

	float baseSize = 10.0f;

	GLfloat v[24] = {
		0.0f * baseSize, 0.0f * baseSize, 0.0f * baseSize,
		0.0f * baseSize, 0.0f * baseSize, 1.0f * baseSize,
		0.0f * baseSize, 1.0f * baseSize, 1.0f * baseSize,
		0.0f * baseSize, 1.0f * baseSize, 0.0f * baseSize,
		1.0f * baseSize, 0.0f * baseSize, 0.0f * baseSize,
		1.0f * baseSize, 0.0f * baseSize, 1.0f * baseSize,
		1.0f * baseSize, 1.0f * baseSize, 1.0f * baseSize,
		1.0f * baseSize, 1.0f * baseSize, 0.0f * baseSize
	};

	GLfloat uv[24] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		0.2f, 0.3f, 1.0f,
		0.1f, 0.8f, 0.2f
	};

	GLushort indexs[36] = { 
		0, 1, 2, 0, 2, 3,
		1, 5, 6, 1, 6, 2,
		4, 5, 6, 4, 6, 7,
		0, 4, 7, 0, 7, 3,
		3, 7, 6, 3, 6, 2,
		0, 4, 5, 0, 5, 1
	};

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), v, GL_STATIC_DRAW);
	objData->vertexBuffer = vertexBuffer;

	GLuint colorBuffer;
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), uv, GL_STATIC_DRAW);
	objData->colorBuffer = colorBuffer;

	GLuint indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLushort), indexs, GL_STATIC_DRAW);
	objData->IndexBuffer = indexBuffer;
	objData->indexNum = 36;
}

void Display3dCube::setVa()
{
	glBindBuffer(GL_ARRAY_BUFFER, objData->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, objData->colorBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}

void Display3dCube::setVc()
{
	posMatrix->identity();
	float pi = 3.1415926;
	Quaternion q(Vector3(0, 1, 0), 0);

	Vector3 pos(0,0,0);

	posMatrix->setTranslation(pos);
	GLuint _projectionSlot = glGetUniformLocation(program, "modelView");
	glUniformMatrix4fv(_projectionSlot, 1, GL_FALSE, &(posMatrix->M[0][0]));

	Matrix *camera = Engine::getCamera()->cameraMatrix;
	_projectionSlot = glGetUniformLocation(program, "camera");
	glUniformMatrix4fv(_projectionSlot, 1, GL_FALSE, &(camera->M[0][0]));
}

vector<BindAttrib> Display3dCube::getBindAtt()
{
	vector<BindAttrib> vec;

	BindAttrib bind0;
	bind0.bindID = 0;
	bind0.bindattribute = "position";
	vec.push_back(bind0);

	BindAttrib bind1;
	bind1.bindID = 1;
	bind1.bindattribute = "color";
	vec.push_back(bind1);

	return vec;
}

std::string Display3dCube::getShaderName()
{
	return "display3dcube_shader";
}

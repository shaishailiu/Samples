#include "Engine.h"
#include "utils/Camera3D.h"
#include "vo/ObjData.h"
#include "utils/BindAttrib.h"
#include "math/Core.h"
#include "Display3dAxis.h"


using namespace std;
Display3dAxis::Display3dAxis()
{
	initData();
}


Display3dAxis::~Display3dAxis()
{
}

void Display3dAxis::initData()
{
	objData = new ObjData();

	float baseSize = 20.0f;
	float ArrowSize = 2.0f;

	GLfloat v[36] = {
		0.0f, 0.0f, 0.0f,
		baseSize, 0.0f, 0.0f,
		baseSize - ArrowSize, 0.0f, ArrowSize,
		baseSize - ArrowSize, 0.0f, -ArrowSize,
		
		0.0f, 0.0f, 0.0f,
		0.0f, baseSize, 0.0f,
		ArrowSize, baseSize - ArrowSize, 0.0f,
		-ArrowSize, baseSize - ArrowSize, 0.0f,

		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, baseSize,
		ArrowSize, 0.0f, baseSize - ArrowSize,
		-ArrowSize, 0.0f, baseSize - ArrowSize
	};

	for (int i = 0;i<36;i++)
	{
		v[i] += 0.1;
	}

	GLfloat uv[36] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f
	};

	GLushort indexs[18] = {
		0, 1, 1, 2, 1, 3,
		4, 5, 5, 6, 5, 7,
		8, 9, 9, 10, 9, 11
	};

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(GLfloat), v, GL_STATIC_DRAW);
	objData->vertexBuffer = vertexBuffer;

	GLuint colorBuffer;
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(GLfloat), uv, GL_STATIC_DRAW);
	objData->colorBuffer = colorBuffer;

	GLuint indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 18 * sizeof(GLushort), indexs, GL_STATIC_DRAW);
	objData->IndexBuffer = indexBuffer;
	objData->indexNum = 18;
}

void Display3dAxis::setVa()
{
	glBindBuffer(GL_ARRAY_BUFFER, objData->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, objData->colorBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}

void Display3dAxis::setVc()
{
	posMatrix->identity();
	//float pi = 3.1415926;
	//Quaternion q(Vector3(0, 1, 0), 0);

	//Vector3 pos(0, 0, 0);

	//posMatrix->setTranslation(pos);
	GLuint _projectionSlot = glGetUniformLocation(program, "modelView");
	glUniformMatrix4fv(_projectionSlot, 1, GL_FALSE, &(posMatrix->M[0][0]));

	Matrix *camera = Engine::getCamera()->cameraMatrix;
	_projectionSlot = glGetUniformLocation(program, "camera");
	glUniformMatrix4fv(_projectionSlot, 1, GL_FALSE, &(camera->M[0][0]));
}

std::vector<BindAttrib> Display3dAxis::getBindAtt()
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

std::string Display3dAxis::getShaderName()
{
	return "display3daxis_shader";
}

void Display3dAxis::draw()
{
	glLineWidth(2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objData->IndexBuffer);
	glDrawElements(GL_LINES, objData->indexNum, GL_UNSIGNED_SHORT, 0);
}

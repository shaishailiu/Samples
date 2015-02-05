#include "Engine.h"
#include "vo/ObjData.h"
#include "utils/BindAttrib.h"
#include "log/LogTrace.h"
#include "math/Vector.h"
#include "math/Matrix.h"
#include "utils/Camera3D.h"
#include "Display3dGrid.h"

using namespace std;

Display3dGrid::Display3dGrid(void)
{
}


Display3dGrid::~Display3dGrid(void)
{
}

void Display3dGrid::initGridNum()
{
	int num = 20;
	float strid = 10;
	int width = num * strid;

	vector<float> vf;
	vector<GLushort> indexf;
	int j=0;
	for(int i=-num;i<num;i++){
		vf.push_back(i * strid);
		vf.push_back(0.0f);
		vf.push_back(width);

		vf.push_back(i * strid);
		vf.push_back(0.0f);
		vf.push_back(-width);

		vf.push_back(width);
		vf.push_back(0.0f);
		vf.push_back(i * strid);

		vf.push_back(-width);
		vf.push_back(0.0f);
		vf.push_back(i * strid);

		indexf.push_back(0 + j * 4);
		indexf.push_back(1 + j * 4);
		indexf.push_back(2 + j * 4);
		indexf.push_back(3 + j * 4);

		j++;
	}

	GLfloat v[12] = {
		-1.0f,  0.0f, 0.0f, 
		1.0f,  0.0f, 0.0f, 
		0.0f, 0.0f, -1.0f,
		0.0f,  0.0f, 1.0f};

	GLushort indexs[4] = {0,1,2,3};

	objData = new ObjData();

	/*
	vector<GLfloat> vf;

	for(int i=0;i<12;i++){
		vf.push_back(v[i]);
	}
	*/
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vf.size() * sizeof(GLfloat), &vf[0], GL_STATIC_DRAW);
	objData->vertexBuffer = vertexBuffer;

	GLuint indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexf.size() * sizeof(GLushort), &indexf[0], GL_STATIC_DRAW);
	objData->IndexBuffer = indexBuffer;
	objData->indexNum = indexf.size();
}

vector<BindAttrib> Display3dGrid::getBindAtt()
{
	vector<BindAttrib> vec;

	BindAttrib bind0;
	bind0.bindID=0;
	bind0.bindattribute="vPosition";
	vec.push_back(bind0);

	return vec;
}

string Display3dGrid::getShaderName()
{
	return "display3dgrid_shader";
}

void Display3dGrid::update()
{
	glUseProgram(program);
	setVa();
	setVc();
	draw();
}

void Display3dGrid::setVa()
{
	glBindBuffer(GL_ARRAY_BUFFER,objData->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0,0);
	glEnableVertexAttribArray(0);

}

void Display3dGrid::setVc()
{

	Matrix *camera = Engine::getCamera()->cameraMatrix;
	GLuint _projectionSlot = glGetUniformLocation(program, "camera");
	glUniformMatrix4fv(_projectionSlot,1,GL_FALSE,&(camera->M[0][0]));

}

void Display3dGrid::draw()
{
	glLineWidth(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,objData->IndexBuffer);
	glDrawElements(GL_LINES, objData->indexNum, GL_UNSIGNED_SHORT, 0);
}

#include "Engine.h"
#include "EngineConfig.h"
#include "layer/LayerManager.h"
#include "utils/Camera3D.h"
#include "utils/BindAttrib.h"
#include "vo/ObjData.h"
#include "math/Matrix.h"
#include "Display3dMap.h"

using namespace std;

Display3dMap::Display3dMap(void)
{
	initData();
}


Display3dMap::~Display3dMap(void)
{
}

vector<BindAttrib> Display3dMap::getBindAtt()
{
	vector<BindAttrib> vec;

	BindAttrib bind0;
	bind0.bindID=0;
	bind0.bindattribute="vPosition";
	vec.push_back(bind0);


	BindAttrib bind1;
	bind1.bindID=1;
	bind1.bindattribute="texcoord";
	vec.push_back(bind1);

	return vec;
}

string Display3dMap::getShaderName()
{
	return "display3dmap_shader";
}
/*
void Display3dMap::initData()
{
	objData = new ObjData();

	GLfloat v[12] = {
		0.0f, 0.0f, 1.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 0.0f, 1.0f};
		
	GLfloat uv[8] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	GLushort indexs[6] = {0, 2, 3, 0, 1, 2};

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), v, GL_STATIC_DRAW);
	objData->vertexBuffer = vertexBuffer;

	GLuint uvBuffer;
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), uv, GL_STATIC_DRAW);
	objData->uvBuffer = uvBuffer;

	GLuint indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLushort), indexs, GL_STATIC_DRAW);
	objData->IndexBuffer = indexBuffer;
	objData->indexNum = 6;
}
*/
void Display3dMap::setVa()
{
	glBindBuffer(GL_ARRAY_BUFFER,objData->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0,0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,objData->uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,0,0);
	glEnableVertexAttribArray(1);
}

void Display3dMap::setVc()
{
	GLuint _textureSlot = glGetUniformLocation(program, "tex0");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, objData->texture);
	glUniform1i(_textureSlot, 0);

	GLuint _whSlot = glGetUniformLocation(program, "wh");
	float num = (Engine::getScene()->getX() + _x - Engine::getConfig()->width/2.0f)*2.0f/Engine::getConfig()->width;
	float num1 = (-Engine::getScene()->getY() + Engine::getConfig()->height/2.0f - _y)*2.0f/Engine::getConfig()->height;

	GLfloat wh[4] = {_width/Engine::getConfig()->width * 2,_height/Engine::getConfig()->height * 2,num,num1};
	glUniform4fv(_whSlot,1,wh);

}
/*
void Display3dMap::draw()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,objData->IndexBuffer);
	glDrawElements(GL_TRIANGLES, objData->indexNum, GL_UNSIGNED_SHORT, 0);
}

void Display3dMap::update()
{
	glUseProgram(program);
	setVa();
	setVc();
	draw();
}
*/
void Display3dMap::setWidth( float w )
{
	_width = w;
}

void Display3dMap::setHeight( float h )
{
	_height = h;
}

void Display3dMap::setWH( const float &w,const float &h )
{
	_width = w;
	_height = h;
}

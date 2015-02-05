#include "vo/ObjData.h"
#include "utils/BindAttrib.h"
#include "Engine.h"
#include "EngineConfig.h"
#include "Display3dUI.h"

using namespace std;
Display3dUI::Display3dUI(void)
{
	initData();

	_regisX = 0;
	_regisY = 0;

	_state = 0;
}


Display3dUI::~Display3dUI(void)
{
}

void Display3dUI::setVa()
{
	glBindBuffer(GL_ARRAY_BUFFER,objData->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0,0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,objData->uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,0,0);
	glEnableVertexAttribArray(1);
}

void Display3dUI::setVc()
{
	GLuint _textureSlot = glGetUniformLocation(program, "tex0");
	glActiveTexture(GL_TEXTURE0);
	if(_state == 0){
		glBindTexture(GL_TEXTURE_2D, objData->texture);
	}else{
		glBindTexture(GL_TEXTURE_2D, _upSkinTexture);
	}
	
	glUniform1i(_textureSlot, 0);
	
	GLuint _whSlot = glGetUniformLocation(program, "wh");
	float num = (_regisX + _x - Engine::getConfig()->width/2.0f)*2.0f/Engine::getConfig()->width;
	float num1 = (- _regisY + Engine::getConfig()->height/2.0f - _y)*2.0f/Engine::getConfig()->height;

	GLfloat wh[4] = {_width/Engine::getConfig()->width * 2,_height/Engine::getConfig()->height * 2,num,num1};
	glUniform4fv(_whSlot,1,wh);
	
}

void Display3dUI::initData()
{
	objData = new ObjData();

	GLfloat v[12] = {
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f};

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

vector<BindAttrib> Display3dUI::getBindAtt()
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

string Display3dUI::getShaderName()
{
	return "display3dui_shader";
}

void Display3dUI::setWH( const float w,const float h )
{
	_width = w;
	_height = h;
}

void Display3dUI::setRegisXY( const float rx,const float ry )
{
	_regisX = rx;
	_regisY = ry;
}

bool Display3dUI::testPoint( const float tx,const float ty )
{
	if((tx > (_x + _regisX)) && (tx < (_x + _width + _regisX)) && (ty > (_y + _regisY)) && (ty < (_y + _height + _regisY))){
		return true;
	}else{
		return false;
	}
}

void Display3dUI::setUpSkin( GLuint _text )
{
	_upSkinTexture = _text;
}

void Display3dUI::setState( const int state )
{
	_state = state;
}

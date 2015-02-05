#include "vo/ObjData.h"
#include "utils/BindAttrib.h"
#include "log/LogTrace.h"
#include "math/Vector.h"
#include "math/Matrix.h"
#include "utils/PngUtil.h"
#include "Display3D.h"
//using namespace grp;

Display3D::Display3D(void)
{
	program = 0;

	visible = true;

	_rotationX = 0;
	_rotationY = 0;
	_rotationZ = 0;

	_x = 0;
	_y = 0;
	_z = 0;

	posMatrix = new Matrix();
	//initData();
}


Display3D::~Display3D(void)
{
}

vector<BindAttrib> Display3D::getBindAtt()
{
	vector<BindAttrib> vec;

	BindAttrib bind0;
	bind0.bindID=0;
	bind0.bindattribute="vPosition";
	vec.push_back(bind0);

	BindAttrib bind1;
	bind1.bindID=1;
	bind1.bindattribute="vColor";
	vec.push_back(bind1);

	BindAttrib bind2;
	bind2.bindID=2;
	bind2.bindattribute="texcoord";
	vec.push_back(bind2);

	return vec;
}

std::string Display3D::getShaderName()
{
	return "display3d_shader";
}

void Display3D::draw()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,objData->IndexBuffer);
	glDrawElements(GL_TRIANGLES, objData->indexNum, GL_UNSIGNED_SHORT, 0);
}


void Display3D::update()
{
	glUseProgram(program);
	setVa();
	setVc();
	draw();
}

void Display3D::initData()
{
	objData = new ObjData();

	GLfloat v[12] = {
		0.0f, 0.0f, 0.99f,
		0.0f, -1.0f, 0.99f,
		1.0f, -1.0f, 0.99f,
		1.0f, 0.0f, 0.99f};

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

void Display3D::setTexture( GLuint texure )
{
	objData->texture = texure;
}

void Display3D::setX( float $x )
{
	_x = $x;
}

void Display3D::setY( float $y )
{
	_y = $y;
}

void Display3D::setZ( float $z )
{
	_z = $z;
}

void Display3D::setRotationY( float $y )
{
	_rotationY = $y;
}

float Display3D::getX()
{
	return _x;
}

float Display3D::getY()
{
	return _y;
}

float Display3D::getZ()
{
	return _z;
}

float Display3D::getRotationX()
{
	return _rotationX;
}

float Display3D::getRotationY()
{
	return _rotationY;
}

float Display3D::getRotationZ()
{
	return _rotationZ;
}

void Display3D::setPosition(const Vector3 &pos)
{
	_position.set(pos.X, pos.Y, pos.Z);
}

void Display3D::setRotation(const Vector3 &rotation)
{
	_rotation.set(rotation.X, rotation.Y, rotation.Z);
}

void Display3D::setScale(const Vector3 &scale)
{
	_scale.set(scale.X, scale.Y, scale.Z);
}

#ifndef _DISPLAY3D_H_
#define _DISPLAY3D_H_

#include <vector>
#include <string>
#include <GLES2/gl2.h>
#include "math/Core.h"

class BindAttrib;
class ObjData;
class Matrix;

class Display3D
{
public:
	Display3D(void);
	~Display3D(void);
	/**shaderProgram*/
	GLuint program;
	//GLfloat vVertices[9];
	//GLfloat color[12];

	ObjData *objData;
	Matrix *posMatrix;

	bool visible;

	void setTexture(GLuint texure);
	void initData();
	virtual void setVa() = 0; 
	virtual void setVc() = 0;
	virtual void draw();
	virtual void update();

	void setX(float $x);
	void setY(float $y);
	void setZ(float $z);

	float getX();
	float getY();
	float getZ();

	float getRotationX();
	float getRotationY();
	float getRotationZ();

	void setRotationY(float $y);

	void setPosition(const Vector3 &pos);
	void setRotation(const Vector3 &rotation);
	void setScale(const Vector3 &scale);

	std::vector<BindAttrib> static getBindAtt();
	std::string static getShaderName();
protected:
	float _rotationX;
	float _rotationY;
	float _rotationZ;
	
	float _x;
	float _y;
	float _z;

	Vector3 _rotation;
	Vector3 _position;
	Vector3 _scale;
};

#endif


#include "Engine.h"
#include "EngineConfig.h"
#include "math/Matrix.h"
#include "math/Vector.h"
#include "math/MathUtils.h"
#include "log/LogTrace.h"
#include "Camera3D.h"


Camera3D::Camera3D(void)
{
	cameraMatrix = new Matrix;
	projMatrix = new Matrix;
	pureCameraMatrix = new Matrix;

	_angleX = 45;
	_angleY = 45;
	_distance = 400;
	_eyePos.set(0.0f, 0.0f, 0.0f);
	_focus.set(0.0f, 0.0f, 0.0f);
	//focus = new Vector3(0,0,0);
	focusX = 0;
	focusY = 0;
	focusZ = 0;
	Quaternion q(0,0,0,0);
	float yscale = 1000.0f/600.0f;

	scaleX = 0.02;
	scaleY = yscale * 0.02;

	//projMatrix->setTransform(Vector3(0,0,0),q,Vector3(scaleX,scaleY,0.0001));
	setWH(1500, 900);
}


Camera3D::~Camera3D(void)
{
	delete cameraMatrix;
}

void Camera3D::setAngleX(float num)
{
	_angleX = num;
	apply();
}

void Camera3D::setAngleY(float num)
{
	_angleY = num;
	apply();
	
}

void Camera3D::setDistance( float num )
{
	if(_distance != num){
		_distance = num;
		apply();
	}
}
/*
void Camera3D::setFous( int x,int y,int z )
{
	focus->X = x;
	focus->Y = y;
	focus->Z = z;
	apply();
}
*/
void Camera3D::apply()
{
	/*
	cameraMatrix->identity();
	pureCameraMatrix->identity();

	Quaternion q;
	float pi = 3.1415926;
	q.setEuler_zxy(Vector3(0,_angleX*pi/180,_angleY*pi/180));

	Matrix ma;
	ma.identity();
	ma.setTranslation(Vector3(-focusX,-focusY,-focusZ));

	cameraMatrix->multiply(ma);

	ma.identity();
	ma.setRotation(q);

	cameraMatrix->multiply(ma);
	cameraMatrix->getInverse(*pureCameraMatrix);
	cameraMatrix->multiply(*projMatrix);
	*/
	//float xpos = 1.0f;
	//float zpos = xpos * tanf(angleToRadianFun(_angleX));
	//float ypos1 = xpos / cosf(angle2radian(_angleX));
	//float ypos = xpos / cosf(angleToRadianFun(_angleX)) * tanf(angleToRadianFun(_angleY));

	//float y1 = 1.0f;
	//float xpos = cosf(angle2Radian(_angleX));
	//float ypos = cosf(angle2Radian(_angleX));
	//float zpos = sinf(angle2Radian(_angleX));

	//Quaternion q(Vector3::Z_AXIS, angle2Radian(_angleY));
	//Quaternion q1(Vector3::Y_AXIS, angle2Radian(_angleX));

	_angleY = int(_angleY) % 360;
	if (_angleY > 90)
	{
		_angleY = 90;
	}else if (_angleY < -90)
	{
		_angleY = -90;
	}


	Matrix ma;
	ma.identity();
	ma.appendRotationAxis(_angleY, Vector3::Z_AXIS);
	ma.appendRotationAxis(_angleX, Vector3::Y_AXIS);

	Vector3 eyePos = ma.transformVector3(Vector3(1, 0, 0));

	//Vector3 eyePos(sinf(angle2Radian(_angleX)), tanf(angle2Radian(_angleY)), cosf(angle2Radian(_angleX)));
	//Vector3 eyePos(-1, 1, 0);
	eyePos.normalize();
	//trace(eyePos.X);
	//trace(eyePos.Y);
	//trace(eyePos.Z);
	//trace("------------------");
	eyePos *= _distance;
	eyePos += _focus;

	cameraMatrix->identity();
	cameraMatrix->buildLookAtLH(eyePos, _focus, Vector3(0, 1, 0));
	//cameraMatrix->buildLookAtRH(Vector3(100, 100, 100), Vector3(0, 0, 0), Vector3(0, 1, 0));
	cameraMatrix->multiply(*projMatrix);
}

Vector3 Camera3D::math2dto3d(float x,float y )
{
	return Vector3();
	x = x * 2.0f / Engine::getConfig()->width - 1;
	y = 1 - y * 2.0f / Engine::getConfig()->height;

	Vector3 v1;
	v1.X = x/scaleX;
	v1.Y = y/scaleY;
	v1.Z = -2000;
	v1 = pureCameraMatrix->transformVector3(v1);

	Vector3 v2;
	v2.X = x/scaleX;
	v2.Y = y/scaleY;
	v2.Z = 2000;
	v2 = pureCameraMatrix->transformVector3(v2);

	Vector3 result;
	result.X = (v2.X - v1.X)*(-v1.Y)/(v2.Y-v1.Y) + v1.X;
	result.Y = 0;
	result.Z = (v2.Z - v1.Z)*(-v1.Y)/(v2.Y-v1.Y) + v1.Z;

	return result;
}

void Camera3D::set2dFous( int x,int y )
{
	return;
	//Vector3 pos = math2dto3d(x,y);

	x = x * 2.0f / Engine::getConfig()->width - 1;
	y = 1 - y * 2.0f / Engine::getConfig()->height;

	Vector3 v1;
	v1.X = x/scaleX;
	v1.Y = y/scaleY;
	v1.Z = 0;
	v1 = pureCameraMatrix->transformVector3(v1);

	Vector3 v2;
	v2.X = x/scaleX;
	v2.Y = y/scaleY;
	v2.Z = 500;
	v2 = pureCameraMatrix->transformVector3(v2);


	Vector3 result;
	focusX = (v2.X - v1.X)*(-v1.Y)/(v2.Y-v1.Y) + v1.X;
	focusY = 0;
	focusZ = (v2.Z - v1.Z)*(-v1.Y)/(v2.Y-v1.Y) + v1.Z;

	apply();
}

void Camera3D::setWH( const int w,const int h )
{
	/*
	Quaternion q(0,0,0,0);
	float yscale = float(w)/float(h);
	scaleY = yscale * 0.02;
	projMatrix->identity();
	projMatrix->setTransform(Vector3(0,0,0),q,Vector3(scaleX,scaleY,0.0001));
	*/


	projMatrix->identity();
	float pi = 3.1415926;
	float aspect = float(w) / float(h);
	float zNear = 0.1;
	float zFar = 1000;
	float fov = 45 * pi / 180;

	projMatrix->buildProjectPerspectiveFovLH(fov, aspect, zNear, zFar);
	//projMatrix->buildProjectPerspectiveFovRH(fov, aspect, zNear, zFar);

	apply();
}

void Camera3D::setFous(float x, float y, float z)
{
	_focus.set(x, y, z);
}

void Camera3D::setFous(const Vector3 &v3d)
{
	_focus.set(v3d.X, v3d.Y, v3d.Z);
}

void Camera3D::addDistance(float num)
{
	//trace(num);
	_distance += num;
	apply();
}

float Camera3D::getAngleX()
{
	return _angleX;
}

float Camera3D::getAngleY()
{
	return _angleY;
}

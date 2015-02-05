#ifndef _CAMERA3D_H_
#define _CAMERA3D_H_

#include "math/Core.h"

class Matrix;

class Camera3D
{
public:
	Camera3D(void);
	~Camera3D(void);

	Matrix *cameraMatrix;
	Matrix *pureCameraMatrix;
	
	float focusX;
	float focusY;
	float focusZ;
	Matrix *projMatrix;
	float scaleX;
	float scaleY;

	void setAngleX(float num);
	float getAngleX();
	void setAngleY(float num);
	float getAngleY();

	void setDistance(float num);
	void addDistance(float num);

	
	void setFous(float x, float y, float z);
	void setFous(const Vector3 &v3d);

	void set2dFous(int x,int y);

	void setWH(const int w,const int h);

	Vector3 math2dto3d(float x,float y );

private:

	Vector3 _eyePos;
	Vector3 _focus;
	float _angleX;
	float _angleY;
	float _distance;
	void apply();


};

#endif


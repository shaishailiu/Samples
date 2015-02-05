#ifndef _MESHVO_H_
#define _MESHVO_H_

#include "math/Matrix.h"
struct ObjectUv
{
	float x;
	float y;
	int a;
	int b;
};

struct ObjectTri
{
	int t0;
	int t1;
	int t2;
};

struct ObjectWeight
{
	int boneId;
	float w;
	float x;
	float y;
	float z;
};

struct ObjectBone
{
	float tx;
	float ty;
	float tz;
	
	float qx;
	float qy;
	float qz;
	float qw;
	
	int changtype;
	int father;
	int startIndex;
	Matrix matrix;

};

#endif
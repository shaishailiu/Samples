#ifndef _PARTICLEBALLDATA_H_
#define _PARTICLEBALLDATA_H_

#include "objdata.h"

class ParticleBallData :
	public ObjData
{
public:
	ParticleBallData(void);
	~ParticleBallData(void);

	GLuint basePosBuffer;
	GLuint beMoveBuffer;

	GLuint textureColor;
};

#endif
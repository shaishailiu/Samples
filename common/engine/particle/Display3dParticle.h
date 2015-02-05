#ifndef _DISPLAY3DPARTICLE_H_
#define _DISPLAY3DPARTICLE_H_

#include <vector>

#include "display/Display3D.h"
#include "ParticleAnimVo.h"
#include "ParticleDisplayVo.h"
#include "ParticleItemVo.h"
#include "ParticleTimeline.h"

class Display3dParticle :
	public Display3D
{
public:
	Display3dParticle(void);
	~Display3dParticle(void);

	//ParticleItemVo pdata;

	GLuint texture;

	ParticleDisplayVo data;
	ParticleTimeline timeline;

	int _time;

	int _beginTime;

	Display3D *bindTarget;

	Matrix bindMatrix;
	Matrix inverseBindMatrix;

	virtual void setInfo(const ParticleItemVo info);

	virtual void setVa(); 
	virtual void setVc();
	
	virtual void updatePosMatrix();

	virtual void watchEye(Matrix *ma);

	void setBlendFactors(const int &type);

	virtual void updateTime(const int time);

	virtual void update();

	virtual void reset();

	int getMaxFrame();
};

#endif

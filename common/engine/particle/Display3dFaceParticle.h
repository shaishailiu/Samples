#ifndef _DISPLAY3DFACEPARTICLE_H_
#define _DISPLAY3DFACEPARTICLE_H_

#include <string>
#include "display3dparticle.h"
#include "ParticleItemVo.h"


class Display3dFaceParticle :
	public Display3dParticle
{
public:
	Display3dFaceParticle(void);
	~Display3dFaceParticle(void);

	float currentUV[2];

	int currentColorIndex;

	virtual void setInfo(const ParticleItemVo info);

	virtual void setVa(); 
	virtual void setVc();
	//virtual void draw();

	//virtual void update();

	virtual void updateTime(const int time);

	void updateUV();
	
	void updateColor();

	void initParticleData();

	vector<BindAttrib> static getBindAtt();
	string static getShaderName();

};

#endif
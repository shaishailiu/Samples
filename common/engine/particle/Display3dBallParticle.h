#ifndef _DISPLAY3DBALLPARTICLE_H_
#define _DISPLAY3DBALLPARTICLE_H_

#include "display3dparticle.h"

class ParticleBallData;

class Display3dBallParticle :
	public Display3dParticle
{
public:
	Display3dBallParticle(void);
	~Display3dBallParticle(void);


	virtual void setVa(); 
	virtual void setVc();

	virtual void setInfo(const ParticleItemVo info);

	virtual void updateTime(const int time);

	virtual void watchEye(Matrix *ma);

	ParticleBallData *getParticleData();

	vector<BindAttrib> static getBindAtt();
	string static getShaderName();
private:
	void initBaseData();
	vector<GLfloat> initBasePos();
	void initSpeed(const vector<GLfloat> &basePos);
	void makeRectangleData(vector<float> &verterList,vector<float> &uvList);
	Matrix getAxisMatrix(const Vector4 v3d);

	//float timeVc[4];
	float currentFrame;

	Matrix *watchMatrix;
};

#endif
#ifndef _PARTICLETIMELINE_H_
#define _PARTICLETIMELINE_H_

#include <vector>
#include "ParticleAnimVo.h"
#include "ParticleDisplayVo.h"
#include "FrameTimeUtils.h"
#include "math/Matrix.h"
#include "ctrl/SelfRotation.h"
#include "ctrl/AxisRotaion.h"
#include "ctrl/Centrifugal.h"
#include "ctrl/AxisMove.h"
#include "ctrl/ColorChange.h"
#include "ctrl/ScaleChange.h"
#include "ctrl/ScaleAnim.h"
#include "ctrl/ScaleNoise.h"

class ParticleTimeline
{
public:
	ParticleTimeline(void);
	~ParticleTimeline(void);

	bool visible;

	int maxFrameNum;

	int beginTime;

	static FrameTimeUtils frameutils;
	
	void setData(const std::vector<ParticleAnimVo> ary);

	void updateTime(const int time);

	void updateMatrix(Matrix *posMatrix,const ParticleDisplayVo &data);

	float getSelfNum();

	void reset();

private:

	std::vector<ParticleAnimVo> _keyFrameAry;
	ParticleAnimVo *_currentKeyFrame;
	int _time;
	int targetFlag;
	
	SelfRotation *_selfRotaion;
	AxisRotaion *_axisRotaion;
	Centrifugal *_centrifugal;
	AxisMove *_axisMove;
	ColorChange *_colorChange;
	ScaleChange *_scaleChange;
	ScaleAnim *_scaleAnim;
	ScaleNoise *_scaleNosie;
	
	void getTarget();

	void enterKeyFrame(const std::vector<ParticleAnimFrameVo> ary,const float baseTime ,const float baseValueAry[]);


};

#endif
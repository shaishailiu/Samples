#ifndef _PARTICLEANIMVO_H_
#define _PARTICLEANIMVO_H_

#include "json/json.h"
#include "ParticleAnimFrameVo.h"

class ParticleAnimVo
{
public:
	ParticleAnimVo(void);
	~ParticleAnimVo(void);

	std::vector<ParticleAnimFrameVo> animframevec;

	int frameNum;

	float baseValue[10];

	void setDataByJson(const Json::Value anim);

};

#endif
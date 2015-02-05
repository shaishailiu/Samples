#ifndef _PARTICLEITEMVO_H_
#define _PARTICLEITEMVO_H_

#include "json/json.h"
#include "ParticleAnimVo.h"
#include "ParticleDisplayVo.h"

class ParticleItemVo
{
public:
	ParticleItemVo(void);
	~ParticleItemVo(void);

	ParticleDisplayVo display;
	std::vector<ParticleAnimVo> timeline;

	void setDataByJson(const Json::Value item);

	void setDisplayVo(const Json::Value dvo);

};

#endif
#ifndef _PARTICLEVO_H_
#define _PARTICLEVO_H_

#include <vector>
#include "ParticleItemVo.h"
#include "json/json.h"

class ParticleVo
{
public:
	ParticleVo(void);
	~ParticleVo(void);

	std::vector<ParticleItemVo> itemVec;

	void setDataByJson(const Json::Value root);
};

#endif
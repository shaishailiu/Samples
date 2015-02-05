#ifndef _PARTICLEANIMFRAMEVO_H_
#define _PARTICLEANIMFRAMEVO_H_

#include "json/json.h"
#include "TypeValue.h"

class ParticleAnimFrameVo
{
public:
	ParticleAnimFrameVo(void);
	~ParticleAnimFrameVo(void);

	//float baseValue;

	std::vector<TypeValue> dataVec;

	int type;

	void setDataByJson(const Json::Value animtype);
};

#endif
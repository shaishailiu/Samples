#include "ParticleAnimFrameVo.h"


ParticleAnimFrameVo::ParticleAnimFrameVo(void)
{
	//baseValue = 0;
}


ParticleAnimFrameVo::~ParticleAnimFrameVo(void)
{
}

void ParticleAnimFrameVo::setDataByJson( const Json::Value animtype )
{
	type = animtype["type"].asInt();
	int s = animtype["data"].size();
	for(int i=0;i<s;i++){
		TypeValue tv;
		tv.setDataByJson(animtype["data"][i]);
		dataVec.push_back(tv);
	}
}

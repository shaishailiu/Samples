#include "ParticleAnimVo.h"


ParticleAnimVo::ParticleAnimVo(void)
	: baseValue(),frameNum(0)
{
	//for(unsigned int i=0;i<10;i++){
	//	baseValue[i] = 0;
	//}
}


ParticleAnimVo::~ParticleAnimVo(void)
{
}

void ParticleAnimVo::setDataByJson( const Json::Value anim )
{
	frameNum = anim["frameNum"].asInt();
	int s = anim["animdata"].size();
	for(int i=0;i<s;i++){
		ParticleAnimFrameVo pafv;
		pafv.setDataByJson(anim["animdata"][i]);
		animframevec.push_back(pafv);
	}

}

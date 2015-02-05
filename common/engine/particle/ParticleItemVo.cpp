#include "ParticleItemVo.h"


ParticleItemVo::ParticleItemVo(void)
{
}


ParticleItemVo::~ParticleItemVo(void)
{
}

void ParticleItemVo::setDataByJson( const Json::Value item )
{
	//animvo.setDataByJson(item["timeline"]);
	int animSize = item["timeline"].size();
	for(int i=0;i<animSize;i++){
		ParticleAnimVo pavo;
		pavo.setDataByJson(item["timeline"][i]);
		timeline.push_back(pavo);
	}

	display.setDataByJson(item["display"]);

}

void ParticleItemVo::setDisplayVo( const Json::Value dvo )
{
	
}

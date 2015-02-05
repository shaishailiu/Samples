 #include "ParticleVo.h"


ParticleVo::ParticleVo(void)
{
}

ParticleVo::~ParticleVo(void)
{
}

void ParticleVo::setDataByJson( const Json::Value root )
{
	int size = root.size();

	for(int i=0;i<size;i++){
		ParticleItemVo pivo;
		pivo.setDataByJson(root[i]);
		itemVec.push_back(pivo);
	}
	
}

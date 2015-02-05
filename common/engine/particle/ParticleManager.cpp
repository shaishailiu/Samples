#include "CombineParticle.h"
#include <algorithm>
#include "Engine.h"
#include "program/ProgramManager.h"
#include "utils/BindAttrib.h"
#include "Display3dFaceParticle.h"
#include "Display3dBallParticle.h"
#include "ParticleManager.h"

using namespace std;

ParticleManager::ParticleManager(void)
{
	Engine::getProgramManager()->registShader(Display3dFaceParticle::getShaderName(),Display3dFaceParticle::getBindAtt()); 
	Engine::getProgramManager()->registShader(Display3dBallParticle::getShaderName(),Display3dBallParticle::getBindAtt()); 
}

ParticleManager::~ParticleManager(void)
{
}

CombineParticle * ParticleManager::loadParticle( const std::string url )
{
	CombineParticle *cp = new CombineParticle;
	
	cp->load(url);

	return cp;
}

void ParticleManager::addParticle( CombineParticle *cp )
{
	particleList.push_back(cp);
}

void ParticleManager::removeParticle( CombineParticle *cp )
{
	//particleList.

	vector<CombineParticle*>::iterator it;
	it = find(particleList.begin(),particleList.end(),cp);

	if(it != particleList.end()){
		particleList.erase(it);
	}
}

void ParticleManager::updateTime(const int t )
{
	for (unsigned int i=0;i<particleList.size();i++)
	{
		particleList[i]->updateTime(t);
	}
}

void ParticleManager::update()
{
	for (unsigned int i=0;i<particleList.size();i++)
	{
		particleList[i]->update();
	}
}

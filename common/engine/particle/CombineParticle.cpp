#include "Engine.h"
#include "EngineConfig.h"
#include "program/ProgramManager.h"
#include "particle/ParticleManager.h"
#include "utils/FileUtils.h"
#include "json/json.h"
#include "ParticleVo.h"
#include "Display3dFaceParticle.h"
#include "Display3dParticle.h"
#include "Display3dBallParticle.h"
#include "display/Display3D.h"
#include "ParticleType.h"
#include "log/LogTrace.h"

#include "CombineParticle.h"

using namespace std;

CombineParticle::CombineParticle(void)
{
	_time = 0;
}


CombineParticle::~CombineParticle(void)
{
}

void CombineParticle::load( const string url )
{
	string s = FileUtils::readTxt(url);
	
	Json::Value root;  
	Json::Reader reader;  
	trace("ready json");
	bool ok = reader.parse(s.c_str(),root);
	trace("ok json");

	ParticleVo pvo;
	pvo.setDataByJson(root);

	for(unsigned int i=0;i<pvo.itemVec.size();i++){

		Display3dParticle *particle;

		if(pvo.itemVec[i].display.particleType == FACE_PARTICLE){
			particle = new Display3dFaceParticle;
			particle->program = Engine::getProgramManager()->getShader(Display3dFaceParticle::getShaderName());
		}else if(pvo.itemVec[i].display.particleType == BALL_PARTICLE){
			particle = new Display3dBallParticle;
			particle->program = Engine::getProgramManager()->getShader(Display3dBallParticle::getShaderName());
		}
		
		particle->setInfo(pvo.itemVec[i]);
		displayVec.push_back(particle);
		
	}

	setMaxNum();
}

void CombineParticle::update()
{
	for(unsigned int i=0;i<displayVec.size();i++){
		displayVec[i]->update();
	}
}

void CombineParticle::updateTime( const int t )
{
	
	_time += t;

	for(unsigned int i=0;i<displayVec.size();i++){
		displayVec[i]->updateTime(_time);
	}

	if(_time >= _maxTime){
		Engine::getParticleManager()->removeParticle(this);
	}

}

void CombineParticle::reset( const int t )
{
	_time = t;

	for(unsigned int i=0;i<displayVec.size();i++){
		displayVec[i]->reset();
	}

}

void CombineParticle::setMaxNum()
{
	_maxTime = 0;
	for(unsigned int i = 0;i<displayVec.size();i++){
		if(_maxTime < displayVec[i]->getMaxFrame()){
			_maxTime = displayVec[i]->getMaxFrame();
		}
	}
	_maxTime = _maxTime * FRAMETIME;
}

void CombineParticle::setBindTarget( Display3D *display )
{
	for(unsigned int i = 0;i<displayVec.size();i++){
		displayVec[i]->bindTarget = display;
	}
}

#include "Engine.h"
#include "particle/ParticleManager.h"
#include "utils/Camera3D.h"
#include "utils/TimeUtil.h"
#include "log/LogTrace.h"
#include "MapLayer.h"
#include "GeomLayer.h"
#include "AvatarLayer.h"
#include "UILayer.h"
#include "math/Vector.h"
#include <GLES2/gl2.h>

#include "LayerManager.h"


LayerManager::LayerManager(void)
{
	mapLayer = new MapLayer();
	geomLayer = new GeomLayer();
	avatarLayer = new AvatarLayer();
	uiLayer = new UILayer();

	x = 0;
	y = 0;

	//setX(200);
	//setY(200);

}


LayerManager::~LayerManager(void)
{
}

void LayerManager::update()
{
	glClearColor(0.1, 0.1, 0.1, 1);
	glClearDepthf(1.0f);
	//glDisable(GL_CULL_FACE);
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT );

	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	
	glEnable(GL_DEPTH_TEST);
	
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); 
	//avatarLayer->updateShadow();
	glBlendFunc(GL_DST_COLOR,GL_ZERO);
	//mapLayer->update();
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);

	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);  

	glEnable(GL_DEPTH_TEST);

	geomLayer->update();

	mapLayer->update();

	//avatarLayer->update();

	glDepthMask(GL_FALSE);
	Engine::getParticleManager()->update();
	//glDepthMask(GL_FALSE);
	glDepthMask(GL_TRUE);


	glDisable(GL_DEPTH_TEST);

	
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);  
	//glDepthMask(GL_FALSE);
	uiLayer->update();
}

void LayerManager::updateTime( int t )
{
	avatarLayer->upateTime(t);

	Engine::getParticleManager()->updateTime(t);
}

void LayerManager::setX( int valuex )
{
	setCamera();
	x = valuex;
}

void LayerManager::setY( int valuey )
{
	setCamera();
	y = valuey;
}

int LayerManager::getX()
{
	return x;
}

int LayerManager::getY()
{
	return y;
}

void LayerManager::setCamera()
{
	Engine::getCamera()->set2dFous(x,y);
}

void LayerManager::setXY( int valuex,int valuey )
{
	if(x != valuex || y != valuey){
		x = valuex;
		y = valuey;
		setCamera();
	}
}

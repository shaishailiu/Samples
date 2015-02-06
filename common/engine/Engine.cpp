#include "log/LogTrace.h"
#include "utils/TimeUtil.h"
#include "EngineConfig.h"
#include "program/ProgramManager.h"
#include "texture/TextureManager.h"
#include "particle/ParticleManager.h"
#include "layer/LayerManager.h"
#include "net/SocketManager.h"
#include "layer/UILayer.h"
#include "analysis/MeshManager.h"
#include "analysis/AnimManager.h"
#include "utils/Camera3D.h"
#include "utils/Fps.h"
#include "utils//FileUtils.h"
#include "Engine.h"
Engine::Engine(void)
{
	_time = 0;
}


Engine::~Engine(void)
{
}

void Engine::start()
{
	trace("engine staring initing");

	engineConfig = new EngineConfig;
	programManager = new ProgramManager;
	meshManager = new MeshManager;
	animManager = new AnimManager;
	textureManager = new TextureManager;
	particleManager = new ParticleManager;
	socketManager = new SocketManager;
	camera = new Camera3D;
	//fps = new Fps;

	layerManager = new LayerManager;
	//camera->setAngleX(-30);
	//camera->setAngleY(45);

	engineConfig->frameTime = 1000/60;
	//camera->setDistance(0.1);
	
	//layerManager->setX(200);
	//layerManager->setY(200);

	_time = TimeUtil::getTimer();

	//unittest.init();
	trace("init complete!");
	socketManager->connect("127.0.0.1", 6469);

/*
#if WIN32
	string url = "./data/uniforms.txt";
#else
	string url = "data/uniforms.txt";
#endif
	Memory *m = FileUtils::loadFile(url.c_str());

	char * s = new char[m->size];
	memcpy(s,m->buffer,m->size);
	trace(s);
*/
}

void Engine::render()
{

	layerManager->update();

}

void Engine::update()
{
	int currentTime = TimeUtil::getTimer();
	int interval = currentTime - _time;
	if(interval < 16){
		return;
	}else{
		_time = currentTime;
	}

	Fps::addTime(interval);

	layerManager->updateTime(interval);

}

void Engine::resize( int $width,int $height )
{
	glViewport(0,0,$width,$height);
	engineConfig->width = $width;
	engineConfig->height = $height;
	//EngineConfig::width = $width;
	//EngineConfig::height = $height;
	camera->setWH($width,$height);

}

 Engine *m_engine = nullptr;

Engine * Engine::getEngine()
{
	if(m_engine == nullptr)
	{
		m_engine = new Engine;
	}
	return m_engine;
}

ProgramManager * Engine::getProgramManager()
{
	return getEngine()->programManager;
}

TextureManager * Engine::getTextureManager()
{
	return getEngine()->textureManager;
}

MeshManager * Engine::getMeshManager()
{
	return getEngine()->meshManager;
}

AnimManager * Engine::getAnimManger()
{
	return getEngine()->animManager;
}

Camera3D * Engine::getCamera()
{
	return getEngine()->camera;
}

LayerManager * Engine::getLayerManager()
{
	return getEngine()->layerManager;
}

EngineConfig * Engine::getConfig()
{
	return getEngine()->engineConfig;
}

LayerManager * Engine::getScene()
{
	return getEngine()->layerManager;
}

UILayer * Engine::getUILyaer()
{
	return getEngine()->layerManager->uiLayer;
}

ParticleManager * Engine::getParticleManager()
{
	return getEngine()->particleManager;
}

StaticMeshManager * Engine::getStaticMeshManager()
{
	return getEngine()->staticMeshManager;
}

SocketManager * Engine::getSocketManager()
{
	return getEngine()->socketManager;
}



/*
Fps * Engine::getFps()
{
	return getEngine()->fps;
}
*/
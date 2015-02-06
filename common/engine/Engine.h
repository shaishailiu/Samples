#ifndef _ENGINE__H_
#define _ENGINE__H_

#include <GLES2/gl2.h>
#include <string>

using namespace std;

class ProgramManager;
class LayerManager;
struct EngineConfig;
class LogTrace;
class TextureManager;
class MeshManager;
class AnimManager;
class ParticleManager;
class StaticMeshManager;
class SocketManager;
class Camera3D;
class UILayer;
class Fps;

#include "test/UnitTesting.h"

class Engine
{
public:
	static Engine *getEngine();
	static ProgramManager *getProgramManager();
	static TextureManager *getTextureManager();
	static MeshManager *getMeshManager();
	static AnimManager *getAnimManger();
	static Camera3D *getCamera();
	static LayerManager *getLayerManager();
	static EngineConfig * getConfig();
	static LayerManager *getScene();
	static UILayer *getUILyaer();
	static ParticleManager *getParticleManager();
	static StaticMeshManager *getStaticMeshManager();
	static SocketManager *getSocketManager();
	//static Fps *getFps();

	EngineConfig *engineConfig;
	ProgramManager *programManager;
	LayerManager *layerManager;
	TextureManager *textureManager;
	MeshManager *meshManager;
	AnimManager *animManager;
	ParticleManager *particleManager;
	StaticMeshManager *staticMeshManager;
	SocketManager *socketManager;
	Camera3D *camera;

	UnitTesting unittest;
	//Fps *fps;

	void resize(int $width,int $height);

	void start();

	void update();

	void render();
protected:
	Engine(void);
	~Engine(void);
	unsigned int _time;
};

#endif
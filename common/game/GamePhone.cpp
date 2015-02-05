#include "Engine.h"
#include "EngineConfig.h"
#include "utils/Camera3D.h"
#include "utils/FileUtils.h"
#include "json/json.h"
#include "utils/Fps.h"
#include "program/ProgramManager.h"
#include "particle/ParticleManager.h"
#include "particle/CombineParticle.h"
#include "layer/LayerManager.h"
#include "layer/AvatarLayer.h"
#include "layer/MapLayer.h"
#include "display/Display3dMovie.h"
#include "math/Vector.h"
#include "math/Matrix.h"
#include "log/LogTrace.h"
#include "UIControl.h"
#include "particle/ParticleVo.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "GamePhone.h"

#define random(x) (rand()%x)

GamePhone::GamePhone(void)
{

}


GamePhone::~GamePhone(void)
{
}

static GamePhone *m_gamephone = nullptr;

GamePhone * GamePhone::getGame()
{
	if(m_gamephone == nullptr)
	{
		m_gamephone = new GamePhone;
	}
	return m_gamephone;
}

Display3dMovie * GamePhone::getMainChar()
{
	return getGame()->mainChar;
}

void GamePhone::init()
{
	mainChar = new Display3dMovie();

	mainChar->program = Engine::getProgramManager()->getShader(Display3dMovie::getShaderName());
	mainChar->shadowProgram = Engine::getProgramManager()->getShader(Display3dMovie::getShadowShaderName());

	mainChar->addMesh(PERROOT + string("mesh/zid38/mesh/hebing.mb"),PERROOT + string("mesh/zid38/texture/niumo.png"));
	mainChar->addMesh(PERROOT + string("mesh/zid38/mesh/toutie.mb"),PERROOT + string("mesh/zid38/texture/niumo.png"));
	mainChar->addMesh(PERROOT + string("mesh/zid38/mesh/wuqi2.mb"),PERROOT + string("mesh/zid38/texture/fuzi.png"));

	mainChar->addAction("stand",PERROOT + string("act/aid5/stand.ab"));
	mainChar->addAction("walk",PERROOT + string("act/aid5/walk.ab"));
	mainChar->addAction("attack_01",PERROOT + string("act/aid5/attack_01.ab"));
	mainChar->addAction("attack_02",PERROOT + string("act/aid5/attack_02.ab"));
	mainChar->addAction("attack_03",PERROOT + string("act/aid5/attack_03.ab"));
	mainChar->addAction("attack_04",PERROOT + string("act/aid5/attack_04.ab"));
	mainChar->addAction("attack_05",PERROOT + string("act/aid5/attack_05.ab"));
	mainChar->addAction("attack_06",PERROOT + string("act/aid5/attack_07.ab"));

	mainChar->play("stand",0);

	mainChar->setX(500);
	mainChar->setZ(300);

	Engine::getLayerManager()->avatarLayer->addAvatar(mainChar);

	Engine::getLayerManager()->mapLayer->loadMap(PERROOT + string("map/map.lmap"));

	//for (unsigned int i=0;i<30;i++){
	//	getMonsterChar();
	//}


	uiControl = new UIControl;

	uiControl->initUI();


	//testjson
	//string s = FileUtils::readTxt("./data/particle/test.lyfm");
	
	//Json::Value root;  
	//Json::Reader reader;  
	//bool ok = reader.parse(s.c_str(),root);
	
	//ParticleVo pvo;
	//pvo.setDataByJson(root);

	//cp = Engine::getParticleManager()->loadParticle("./data/particle/test.lyfm");

	//cp->setBindTarget(GamePhone::getMainChar());

}


Display3dMovie * GamePhone::getMonsterChar()
{

	Display3dMovie *monsterChar = new Display3dMovie();

	monsterChar->program = Engine::getProgramManager()->getShader(Display3dMovie::getShaderName());
	monsterChar->shadowProgram = Engine::getProgramManager()->getShader(Display3dMovie::getShadowShaderName());

	monsterChar->addMesh(PERROOT + string("mesh/zid480/mesh/shenti.mb"),PERROOT + string("mesh/zid480/texture/chishatangdizi.png"));

	monsterChar->addAction("stand",PERROOT + string("act/aid442/stand.ab"));
	monsterChar->addAction("walk",PERROOT + string("act/aid442/walk.ab"));
	monsterChar->addAction("injured",PERROOT + string("act/aid442/injured.ab"));
	monsterChar->addAction("death",PERROOT + string("act/aid442/death.ab"));

	monsterChar->play("stand",0);

	float ranx = random(100)/100.0f * 800;
	float rany = random(100)/100.0f * 480;

	monsterChar->setX(ranx);
	monsterChar->setZ(rany);

	monsterChar->setRotationY(random(100)/100.0f * 360);

	Engine::getLayerManager()->avatarLayer->addAvatar(monsterChar);

	return monsterChar;
}

void GamePhone::keyHander(const bool key[] )
{
	
	
	bool isWalk = false;
	
	if(key[74]){
		mainChar->speedX = 0;
		mainChar->speedZ = 0;

		mainChar->play("attack_01",0);
		return;
	}else if(key[75]){
		mainChar->speedX = 0;
		mainChar->speedZ = 0;

		mainChar->play("attack_02",0);
		return;
	}else if(key[76]){
		 mainChar->speedX = 0;
		mainChar->speedZ = 0;

		mainChar->play("attack_03",0);
		return;
	}else if(key[85]){
		mainChar->speedX = 0;
		mainChar->speedZ = 0;

		mainChar->play("attack_04",0);
		return;
	}else if(key[73]){
		mainChar->speedX = 0;
		mainChar->speedZ = 0;

		mainChar->play("attack_05",0);
		return;
	}else if(key[79]){
		mainChar->speedX = 0;
		mainChar->speedZ = 0;

		mainChar->play("attack_06",0);
		return;
	}
	
	Vector2 speed;

	int angle = 0;


	if(key[87]){//ио
		if(key[65]){//вС
			speed.set(-1,-1);
			angle = 270;
		}else if(key[68]){//ср
			speed.set(1,-1);
			angle = 0;
		}else{
			speed.set(0,-1);
			angle = 315;
		}
		isWalk = true;
	}else if(key[83]){//об
		if(key[65]){
			speed.set(-1,1);
			angle = 180;
		}else if(key[68]){
			speed.set(1,1);
			angle = 90;
		}else{
			speed.set(0,1);
			angle = 135;
		}
		isWalk = true;
	}else if(key[68]){
		speed.set(1,0);
		angle = 45;
		isWalk = true;
	}else if(key[65]){
		speed.set(-1,0);
		angle = 225;
		isWalk = true;
	}

	speed.normalize();

	if(isWalk){
		mainChar->speedX = speed.X * 0.2;
		mainChar->speedZ = speed.Y * 0.2;

		mainChar->setRotationY(angle);
		mainChar->play("walk",0);
	}else{
		mainChar->speedX = 0;
		mainChar->speedZ = 0;

		mainChar->play("stand",0);
	}
	

	//mainChar->play("stand",0);
}

void GamePhone::update()
{
	//Engine::getCamera()->set2dFous(mainChar->getX(),mainChar->getZ());
	
	Engine::getEngine()->update();

	int sx = Engine::getConfig()->width/2.0f - mainChar->getX();
	int sy = Engine::getConfig()->height/2.0f - mainChar->getZ();
	

	if(sx > 0){
		sx = 0;
	}else if(sx < (Engine::getConfig()->width - Engine::getConfig()->mapWidth)){
		sx = (Engine::getConfig()->width - Engine::getConfig()->mapWidth);
	}

	if(sy > 0){
		sy = 0;
	}else if(sy < (Engine::getConfig()->height - Engine::getConfig()->mapHeight)){
		sy = (Engine::getConfig()->height - Engine::getConfig()->mapHeight);
	}

	
	Engine::getScene()->setXY(sx,sy);

	Engine::getEngine()->render();
}

void GamePhone::mouseDownHander( int x,int y )
{
	//mainChar->play("attack_01",0);

	uiControl->mouseDown(x,y);

	//trace(Engine::getFps()->frame);
	//trace(Fps::frame);
}

void GamePhone::mouseMoveHander( int x,int y )
{
	uiControl->mouseMove(x,y);
}

void GamePhone::mouseUpHander( int x,int y )
{
	uiControl->mouseUp();
}





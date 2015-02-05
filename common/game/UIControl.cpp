#include "display/Display3dUI.h"
#include "Engine.h"
#include "EngineConfig.h"
#include "utils/Camera3D.h"
#include "texture/TextureManager.h"
#include "program/ProgramManager.h"
#include "particle/ParticleManager.h"
#include "particle/CombineParticle.h"
#include "layer/LayerManager.h"
#include "layer/UILayer.h"
#include "log/LogTrace.h"
#include "math/Vector.h"
#include "GamePhone.h"
#include "display/Display3dMovie.h"
#include <math.h>
#include "UIControl.h"


UIControl::UIControl(void)
{
	//initUI();
}


UIControl::~UIControl(void)
{
}

void UIControl::initUI()
{
	directionBtn = getUI("ui/btnup.png","",128.0f,128.0f,120,Engine::getConfig()->height - 120,-64.0f,-64.0f);
	Engine::getUILyaer()->addChild(directionBtn);

	directionBgBtn = getUI("ui/btnbg.png","",128.0f,128.0f,120,Engine::getConfig()->height - 120,-64.0f,-64.0f);
	Engine::getUILyaer()->addChildAt(directionBgBtn,0);

	basePos.set(120,Engine::getConfig()->height - 120);

	skill1 = getUI("ui/00_00.png","ui/00_01.png",64.0f,64.0f,Engine::getConfig()->width - 150 ,Engine::getConfig()->height - 150,-32.0f,-32.0f);
	Engine::getUILyaer()->addChild(skill1);

	skill2 = getUI("ui/01_00.png","ui/01_01.png",64.0f,64.0f,Engine::getConfig()->width - 180 ,Engine::getConfig()->height - 80,-32.0f,-32.0f);
	Engine::getUILyaer()->addChild(skill2);

	skill3 = getUI("ui/02_00.png","ui/02_01.png",64.0f,64.0f,Engine::getConfig()->width - 80 ,Engine::getConfig()->height - 180,-32.0f,-32.0f);
	Engine::getUILyaer()->addChild(skill3);

	attackBtn = getUI("ui/attack.png","ui/attack01.png",128.0f,128.0f,Engine::getConfig()->width - 88 ,Engine::getConfig()->height - 88,-64.0f,-64.0f);
	Engine::getUILyaer()->addChildAt(attackBtn,0);

	isDrag = false;

	cp = Engine::getParticleManager()->loadParticle(PERROOT + string("particle/lid50.lyf"));
	cp->setBindTarget(GamePhone::getMainChar());

	cp2 = Engine::getParticleManager()->loadParticle(PERROOT + string("particle/lid55.lyf"));
	cp2->setBindTarget(GamePhone::getMainChar());

	cp3 = Engine::getParticleManager()->loadParticle(PERROOT + string("particle/lid56.lyf"));
	cp3->setBindTarget(GamePhone::getMainChar());

	cp4 = Engine::getParticleManager()->loadParticle(PERROOT + string("particle/lid57.lyf"));
	cp4->setBindTarget(GamePhone::getMainChar());

	cp5 = Engine::getParticleManager()->loadParticle(PERROOT + string("particle/lid61.lyf"));
	cp5->setBindTarget(GamePhone::getMainChar());

	
}

void UIControl::mouseDown( const int x,const int y )
{
	if(GamePhone::getMainChar()->isLock){
		return;
	}
	
	if(skill1->testPoint(x,y)){
		skill1->setState(1);
		GamePhone::getMainChar()->play("attack_04",1);

		cp3->reset(0);
		Engine::getParticleManager()->addParticle(cp3);

		GamePhone::getMainChar()->isLock = true;
		stopMove();

		return;
	}

	if(skill2->testPoint(x,y)){
		skill2->setState(1);
		GamePhone::getMainChar()->play("attack_02",1);

		cp2->reset(0);
		Engine::getParticleManager()->addParticle(cp2);

		GamePhone::getMainChar()->isLock = true;
		stopMove();
		return;
	}

	if(skill3->testPoint(x,y)){
		skill3->setState(1);
		GamePhone::getMainChar()->play("attack_03",1);

		cp4->reset(0);
		Engine::getParticleManager()->addParticle(cp4);

		GamePhone::getMainChar()->isLock = true;
		stopMove();
		return;
	}

	if(attackBtn->testPoint(x,y)){
		attackBtn->setState(1);

		Engine::getParticleManager()->removeParticle(cp5);
		cp5->reset(0);
		Engine::getParticleManager()->addParticle(cp5);
		/*
		GamePhone::getMainChar()->play("attack_01",1);

		cp->reset(0);
		Engine::getParticleManager()->addParticle(cp);

		GamePhone::getMainChar()->isLock = true;
		stopMove();
		*/
		return;
	}


	isDrag = directionBtn->testPoint(x,y);

	if(isDrag){
		GamePhone::getMainChar()->play("walk",0);
	}

}

Display3dUI * UIControl::getUI( string name,string upName,float w,float h,float x,float y ,float rx,float ry)
{
	Display3dUI *btn = new Display3dUI;
	btn->program = Engine::getProgramManager()->getShader(Display3dUI::getShaderName());
	string url;
	url += PERROOT;
	url += name;
	btn->setTexture(Engine::getTextureManager()->getPngTexture(url.c_str()));

	url.clear();
	url += PERROOT;
	url += upName;

	if(upName.length() > 0){
		btn->setUpSkin(Engine::getTextureManager()->getPngTexture(url.c_str()));
	}

	btn->setWH(w,h);
	btn->setRegisXY(rx,ry);
	btn->setX(x);
	btn->setY(y);
	return btn;
}

void UIControl::mouseMove( const int x,const int y )
{
	if(!isDrag){
		return;
	}

	Vector2 direct;
	direct.set(x - basePos.X,y - basePos.Y);
	direct.normalize();

	GamePhone::getMainChar()->speedX = direct.X * 0.2;
	GamePhone::getMainChar()->speedZ = direct.Y * 0.2;
	

	Vector3 pos = Engine::getCamera()->math2dto3d(Engine::getScene()->getX() + direct.X * 1000,Engine::getScene()->getX() + direct.Y * 1000);
	Vector3 pos2 = Engine::getCamera()->math2dto3d(Engine::getScene()->getX(),Engine::getScene()->getY());
	
	pos = pos - pos2;

	float angle = atan(pos.X/pos.Z) * 180 /PI;

	if(pos.Z < 0){
		angle = angle + 180;
	}
	
	//angle = angle + 180;
	
	direct = direct * 60;
	direct = basePos + direct;

	directionBtn->setX(direct.X);
	directionBtn->setY(direct.Y);
	
	GamePhone::getMainChar()->setRotationY(angle);

}

void UIControl::mouseUp()
{
	stopMove();

	skill1->setState(0);
	skill2->setState(0);
	skill3->setState(0);
	attackBtn->setState(0);
}

void UIControl::stopMove()
{
	directionBtn->setX(basePos.X);
	directionBtn->setY(basePos.Y);

	GamePhone::getMainChar()->speedX = 0;
	GamePhone::getMainChar()->speedZ = 0;

	GamePhone::getMainChar()->play("stand",0);

	isDrag = false;
}

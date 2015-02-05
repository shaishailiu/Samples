#include "Engine.h"
#include "log/LogTrace.h"
#include "display/Display3D.h"
#include "display/Display3dMovie.h"
#include "utils/BindAttrib.h"
#include "program/ProgramManager.h"
#include "texture/TextureManager.h"
#include "analysis/MeshManager.h"
#include "analysis/AnimManager.h"
#include "utils/FileUtils.h"
#include "utils/TimeUtil.h"
#include "AvatarLayer.h"

using namespace std;
AvatarLayer::AvatarLayer(void)
{
	regShaer();
	/*
	display3dMovie = new Display3dMovie;

	display3dMovie->play("stand",0);
	display3dMovie->program = Engine::getProgramManager()->getShader(Display3dMovie::getShaderName());

	string url;
	url.append("./data/mesh/zid34/mesh/niumotoubu.mb");
	string texturl;;
	texturl.append("./data/mesh/zid34/texture/niumo.png");

	display3dMovie->addMesh(url,texturl);

	url.clear();
	texturl.clear();
	url.append("./data/mesh/zid34/mesh/shangxiahebing.mb");
	texturl.append("./data/mesh/zid34/texture/niumo.png");
	display3dMovie->addMesh(url,texturl);

	url.clear();
	texturl.clear();
	url.append("./data/mesh/zid34/mesh/niumowq1.mb");
	texturl.append("./data/mesh/zid34/texture/fuzi_color.png");
	display3dMovie->addMesh(url,texturl);


	url.clear();
	url.append("./data/act/aid5/stand.ab");
	display3dMovie->addAction("stand",url);
	url.clear();
	url.append("./data/act/aid5/walk.ab");
	display3dMovie->addAction("walk",url);
	url.clear();
	url.append("./data/act/aid5/attack_01.ab");
	display3dMovie->addAction("attack_01",url);
	*/
}


AvatarLayer::~AvatarLayer(void)
{

}

void AvatarLayer::update()
{
	//display3dMovie->update();
	for(unsigned int i=0;i<_avatarList.size();i++){
		_avatarList[i]->update();
	}
}

void AvatarLayer::regShaer()
{
	Engine::getProgramManager()->registShader(Display3dMovie::getShaderName(),Display3dMovie::getBindAtt());
	Engine::getProgramManager()->registShader(Display3dMovie::getShadowShaderName(),Display3dMovie::getBindAtt());
}

void AvatarLayer::upateTime( int t )
{
	//display3dMovie->updateTime($time);
	for(unsigned int i=0;i<_avatarList.size();i++){
		_avatarList[i]->updateTime(t);
	}
}

void AvatarLayer::addAvatar( Display3dMovie *mc )
{
	_avatarList.push_back(mc);
}

void AvatarLayer::updateShadow()
{
	for(unsigned int i=0;i<_avatarList.size();i++){
		_avatarList[i]->updateShadow();
	}
}

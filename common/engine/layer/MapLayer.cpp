#include "Engine.h"
#include "EngineConfig.h"
#include "log/LogTrace.h"
#include "display/Display3D.h"
#include "display/Display3dMovie.h"
#include "display/Display3dMap.h"
#include "display/Display3dStaticMesh.h"
#include "utils/BindAttrib.h"
#include "program/ProgramManager.h"
#include "texture/TextureManager.h"
#include "analysis/MeshManager.h"
#include "analysis/AnimManager.h"
#include "utils/FileUtils.h"
#include "utils/TimeUtil.h"
#include "utils/StringUtils.h"
#include "utils/BitmapDatas.h"
#include "log/LogTrace.h"
#include "utils/Memory.h"
#include "utils/FileUtils.h"
#include "math/Core.h"
#include "MapLayer.h"


#define MAPSIZE 256

MapLayer::MapLayer(void)
{
	regShaer();
	/*
	for(int i=0;i<5;i++){
		for(int j=0;j<4;j++){
			Display3dMap *map = new Display3dMap;
			map->program = Engine::getProgramManager()->getShader(Display3dMap::getShaderName());
			string name;
			name += PERROOT;
			name += "map/syc/" + StringUtils::int2str(i + 7) + "_" + StringUtils::int2str(j + 11) + ".png";
			map->setTexture(Engine::getTextureManager()->getPngTexture(name));

			map->setWH(MAPSIZE,MAPSIZE);
			map->setX(i * MAPSIZE);
			map->setY(j * MAPSIZE);
			maplist.push_back(map);
		}
	}

	Engine::getConfig()->mapWidth = 5 * MAPSIZE;
	Engine::getConfig()->mapHeight = 4 * MAPSIZE;
	*/
}


MapLayer::~MapLayer(void)
{
}


void MapLayer::regShaer()
{
	Engine::getProgramManager()->registShader(Display3D::getShaderName(),Display3D::getBindAtt());
	Engine::getProgramManager()->registShader(Display3dMap::getShaderName(),Display3dMap::getBindAtt());
	Engine::getProgramManager()->registShader(Display3dStaticMesh::getShaderName(), Display3dStaticMesh::getBindAtt());
	//Engine::getProgramManager()->registShader(Display3dMovie::getShaderName(),Display3dMovie::getBindAtt());

}


void MapLayer::update(){
	//unsigned int t = TimeUtil::getTimer();
	//trace(t);
	//trace("µØÍ¼²ãäÖÈ¾");
	//display3dMovie->update();
	//display3d->update();
	//map->update();
	for (unsigned int i = 0; i<mapItemList.size(); i++){
		mapItemList[i]->update();
	}
}

void MapLayer::loadMap(string fileUrl)
{
	Memory *memory = FileUtils::loadFile(fileUrl.c_str());

	if (memory == NULL){
		return;
	}

	int itemLength;
	memory->read(&itemLength, sizeof(int));

	for (int i = 0; i<itemLength; i++)
	{
		string meshUrl = PERROOT + memory->readString();
		string normalTextureUrl = PERROOT + memory->readString();
		string textureUrl = PERROOT + memory->readString();

		Vector3 pos(memory->readFloat(), memory->readFloat(), memory->readFloat());
		Vector3 rotation(memory->readFloat(), memory->readFloat(), memory->readFloat());
		Vector3 scale(memory->readFloat(), memory->readFloat(), memory->readFloat());

		/*
		if (rotation.X !=0 || rotation.Y !=0 || rotation.Z != 0)
		{
			trace(rotation.X);
			trace(rotation.Y);
			trace(rotation.Z);
			trace("--------------");
		}
		*/

		Vector3 pos1;
		pos1.set(pos.Z, pos.X, pos.Y);
		pos = pos1;

		float s = 0.2;
		pos *= s;
		scale *= s;
		
		Display3dStaticMesh *staticMesh = new Display3dStaticMesh();
		staticMesh->setPosition(pos);
		staticMesh->setRotation(rotation);
		staticMesh->setScale(scale);

		staticMesh->setObjUrl(meshUrl, textureUrl);
		staticMesh->program = Engine::getProgramManager()->getShader(Display3dStaticMesh::getShaderName());

		mapItemList.push_back(staticMesh);
	}

}


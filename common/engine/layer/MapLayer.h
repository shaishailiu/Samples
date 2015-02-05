#ifndef _MAPLAYER_H_
#define _MAPLAYER_H_

#include <vector>
#include <string>
#include "BaseLayer.h"

class Display3D;
class Display3dMovie;
class Display3dMap;

using namespace std;
class MapLayer : public BaseLayer
{
public:
	MapLayer(void);
	~MapLayer(void);

	virtual void update();

	Display3dMap *map;
	std::vector<Display3dMap*> maplist;

	std::vector<Display3D*> mapItemList;

	void loadMap(string fileUrl);

private:
	void regShaer();
};

#endif


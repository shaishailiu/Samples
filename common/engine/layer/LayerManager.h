#ifndef _LAYMANAGER_H_
#define _LAYMANAGER_H_

class MapLayer;
class GeomLayer;
class AvatarLayer;
class UILayer;

class LayerManager
{
public:
	LayerManager(void);
	~LayerManager(void);


	MapLayer *mapLayer;
	GeomLayer *geomLayer;
	AvatarLayer *avatarLayer;
	UILayer *uiLayer;

	void update();
	void updateTime(int $time);

	void setX(int valuex);
	void setY(int valuey);

	void setXY(int valuex,int valuey);

	void setCamera();

	int getX();
	int getY();
private:
	int x;
	int y;
};

#endif

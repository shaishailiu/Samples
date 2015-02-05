#ifndef _GEOMLYAER_H_
#define _GEOMLYAER_H_

#include "baselayer.h"

class Display3dGrid;
class Display3dCube;
class Display3dAxis;

class GeomLayer :
	public BaseLayer
{
public:
	GeomLayer(void);
	~GeomLayer(void);
	virtual void update();

	Display3dGrid *grid;

	Display3dCube *cube;

	Display3dAxis *axis;
};

#endif
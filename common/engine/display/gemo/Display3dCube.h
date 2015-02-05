#ifndef _DISPLAY3DCUBE_H_
#define _DISPLAY3DCUBE_H_


#include "display/Display3D.h"
class Display3dCube :
	public Display3D
{
public:
	Display3dCube();
	~Display3dCube();

	void initCubeData();

	void setVa();
	void setVc();
	//void draw();
	//void update();

	vector<BindAttrib> static getBindAtt();
	string static getShaderName();

};

#endif // !_DISPLAY3DCUBE_H_


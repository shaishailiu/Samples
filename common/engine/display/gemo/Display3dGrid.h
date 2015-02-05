#ifndef _DISPLAY3DGRID_H_
#define _DISPLAY3DGRID_H_

#include "display/display3d.h"
class Display3dGrid :
	public Display3D
{
public:
	Display3dGrid(void);
	~Display3dGrid(void);
	void initGridNum();

	void setVa(); 
	void setVc();
	void draw();
	void update();

	vector<BindAttrib> static getBindAtt();
	string static getShaderName();
};

#endif

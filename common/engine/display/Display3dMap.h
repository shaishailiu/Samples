#ifndef _DISPLAY3DMAP_H_
#define _DISPLAY3DMAP_H_

#include "display3d.h"

class Display3dMap :
	public Display3D
{
public:
	Display3dMap(void);
	~Display3dMap(void);

	//void initData();
	void setVa(); 
	void setVc();
	//void draw();
	//void update();

	void setWidth(float w);
	void setHeight(float h);
	void setWH(const float &w,const float &h);

	std::vector<BindAttrib> static getBindAtt();
	std::string static getShaderName();
private:
	float _width;
	float _height;
};

#endif


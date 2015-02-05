#ifndef _DISPLAY3DAXIS_H_
#define _DISPLAY3DAXIS_H_


#include "display/Display3D.h"
class Display3dAxis :
	public Display3D
{
public:
	Display3dAxis();
	~Display3dAxis();

	void initData();

	void setVa();
	void setVc();

	void draw();

	std::vector<BindAttrib> static getBindAtt();
	std::string static getShaderName();
};

#endif // !_DISPLAY3DAXIS_H_
#ifndef _DISPLAY3DUI_H_
#define _DISPLAY3DUI_H_

#include "display3d.h"
#include <string>

class Display3dUI :
	public Display3D
{
public:
	Display3dUI(void);
	~Display3dUI(void);

	void initData();

	void setVa(); 
	void setVc();

	void setWH(const float w,const float h);
	void setRegisXY(const float rx,const float ry);

	bool testPoint(const float tx,const float ty);

	void setUpSkin(GLuint _text);
	void setState(const int state);

	std::vector<BindAttrib> static getBindAtt();
	std::string static getShaderName();

private:
	float _width;
	float _height;

	float _regisX;
	float _regisY;

	GLuint _upSkinTexture;

	int _state;
};

#endif
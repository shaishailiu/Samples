#ifndef _DISPLAY3DSTATICMESH_H_
#define _DISPLAY3DSTATICMESH_H_

#include "Display3D.h"
#include "math/Core.h"
#include "utils/BindAttrib.h"

class Display3dStaticMesh :
	public Display3D
{
public:
	Display3dStaticMesh();
	~Display3dStaticMesh();

	void setObjUrl(const string &url, const string &textureurl);

	void setVa();
	void setVc();
	void draw();
	//void update();

	std::vector<BindAttrib> static getBindAtt();
	std::string static getShaderName();
private:
	Matrix rotationMatrix;
};

#endif // !_DISPLAY3DSTATICMESH_H_
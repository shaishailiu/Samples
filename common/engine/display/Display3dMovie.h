#ifndef _DISPLAY3DMOVIE_H_
#define _DISPLAY3DMOVIE_H_

#include "display3d.h"

#include <vector>
#include <GLES2/gl2.h>
#include <string>
#include <map>

class MeshData;
class AnimData;

using namespace std;

class Display3dMovie :
	public Display3D
{
public:
	Display3dMovie(void);
	~Display3dMovie(void);

	float speedX;
	float speedZ;

	bool isLock;

	GLuint shadowProgram;

	void initData();
	void setVa(); 
	void setVc();
	void draw();
	void update();
	void updateTime(int $time);

	void addMesh(const string &url,const string &textureurl);
	void meshComplete(MeshData * meshData);
	void addAction(const char * actionName,const string &url);
	//void addAction(const char *actionName,const char* url);
	//void addABC(const int n);
	void play(string action,int $completeState);
	void updateShadow();

	vector<BindAttrib> static getBindAtt();
	string static getShaderName();
	string static getShadowShaderName();

	string _action;

protected:
	vector<MeshData*> *meshList;
	map<string,AnimData*> *actionDic;
	
	int _frame;
	int _time;
	int _completeState;
	void updateMesh(MeshData *meshData);
	void updateTexture(MeshData *meshData);
};

#endif
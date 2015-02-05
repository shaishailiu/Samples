#ifndef _PROGRAMMANAGER_H_
#define _PROGRAMMANAGER_H_

#include <string>
#include <GLES2/gl2.h>
#include <vector>
#include <map>

using namespace std;

class BindAttrib;

class ProgramManager
{
public:
	ProgramManager();
	~ProgramManager();

	int registShader(string shaderName,const vector<BindAttrib> &vecBindatt);
	int registShaderSource(string shaderName,string &vetexString,string &fragementString,const vector<BindAttrib> &vecBindatt);
	GLuint getShader(string shaderName);
private:
	map<string,GLuint> *shaderMap;

	GLuint loadShader(GLenum type,const char *shaderSrc);
};

#endif

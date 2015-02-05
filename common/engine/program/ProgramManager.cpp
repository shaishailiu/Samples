#include "log/LogTrace.h"
#include <stdlib.h>
#include "utils/BindAttrib.h"
#include "utils/FileUtils.h"

#include "ProgramManager.h"
#if ANDROID
#define BASEROOT "data/shader/"
#else
#define BASEROOT "./data/shader/"
#endif
#define VERTEXURL "_vertex.glsl";
#define FRAGMENTURL "_fragment.glsl";

ProgramManager::ProgramManager()
{
	shaderMap = new map<string,GLuint>;
}


ProgramManager::~ProgramManager()
{
}

GLuint ProgramManager::loadShader( GLenum type,const char *shaderSrc )
{
	GLuint shader;
	GLint compiled;

	shader = glCreateShader(type);

	if(shader == 0){
		return 0;
	}

	glShaderSource(shader,1,&shaderSrc,NULL);
	glCompileShader(shader);

	glGetShaderiv(shader,GL_COMPILE_STATUS,&compiled);

	if(!compiled){
		GLint infoLen = 0;
		glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&infoLen);
		if(infoLen > 1){
			char *infoLog = (char *)malloc (sizeof(char) * infoLen);
			glGetShaderInfoLog(shader,infoLen,NULL,infoLog);
			trace("shader compile error :");
			trace(infoLog);
			free(infoLog);
		}

		glDeleteShader(shader);
		return 0;
	}

	return shader;
}


int ProgramManager::registShaderSource( string shaderName,string &vetexString,string &fragementString ,const vector<BindAttrib> &vecBindatt)
{
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint programObject;
	GLint linked;

	vertexShader = loadShader(GL_VERTEX_SHADER,vetexString.c_str());
	fragmentShader = loadShader(GL_FRAGMENT_SHADER,fragementString.c_str());
	programObject = glCreateProgram();
	if(programObject == 0){
		return 0;
	}

	glAttachShader(programObject,vertexShader);
	glAttachShader(programObject,fragmentShader);

	vector<BindAttrib>::const_iterator iter;

	for(iter = vecBindatt.begin();iter != vecBindatt.end();iter++){
		glBindAttribLocation(programObject,iter->bindID,iter->bindattribute.c_str());
	}

	glLinkProgram(programObject);

	glGetProgramiv(programObject,GL_LINK_STATUS,&linked);

	if(!linked){
		GLint infoLen = 0;
		glGetProgramiv(programObject,GL_INFO_LOG_LENGTH,&infoLen);
		if(infoLen > 1){
			char *infoLog = (char *)malloc(sizeof(char) * infoLen);
			glGetProgramInfoLog(programObject,infoLen,NULL,infoLog);
			trace("programe bind error :",infoLog);
			free(infoLog);
		}
		glDeleteProgram(programObject);
		return 0;
	}

	trace(programObject);

	shaderMap->insert(std::make_pair(shaderName,programObject));

	return 1;
}

GLuint ProgramManager::getShader( string shaderName )
{
	return (*shaderMap)[shaderName];
}

int ProgramManager::registShader( string shaderName,const vector<BindAttrib> &vecBindatt )
{
	string vFileUrl = BASEROOT + shaderName + VERTEXURL;
	string fFileUrl = BASEROOT + shaderName + FRAGMENTURL;
	
	string vertexShaderStr = FileUtils::readTxt(vFileUrl);
	string fragmentShaderStr = FileUtils::readTxt(fFileUrl);

	//trace(vertexShaderStr.c_str());

	registShaderSource(shaderName,vertexShaderStr,fragmentShaderStr,vecBindatt);

	return 1;
}



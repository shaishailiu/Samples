#ifndef _OBJDATA_H_
#define _OBJDATA_H_

#include <GLES2/gl2.h>

class ObjData
{
public:
	ObjData(void);
	~ObjData(void);
	GLuint vertexBuffer;
	GLuint normalBuffer;
	GLuint colorBuffer;
	GLuint uvBuffer;
	GLuint uv2Buffer;
	GLuint IndexBuffer;
	GLuint texture;
	int indexNum;
};

#endif


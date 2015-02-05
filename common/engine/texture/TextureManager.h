#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include <string>
#include <vector>
#include <map>
#include <GLES2/gl2.h>

using namespace std;

class BitmapDatas;

class TextureManager
{
public:
	TextureManager(void);
	~TextureManager(void);
	//GLuint getTgaTexture(string fileUrl);
	GLuint getPngTexture(string fileUrl,bool repeat = false);
	GLuint getBitmapTexture(BitmapDatas *bmp,bool repeat);

	bool hasCache(string &fileUrl );

	map<string,GLuint> textureDic;
};

#endif


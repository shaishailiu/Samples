#ifndef _BITMAPDATAS_H_
#define _BITMAPDATAS_H_
#include <GLES2/gl2.h>

class ColorTransition;

class BitmapDatas
{
public:
	BitmapDatas(const int &w,const int &h,const unsigned int &color);
	~BitmapDatas(void);
	int width;
	int height;
	GLenum format;
	unsigned char *texels;

	void setPixel(const unsigned int &xpos,const unsigned int &ypos,const unsigned int &color);
	void setPixelByColorTransition(const ColorTransition &ct,const unsigned int &ypos);
};

#endif
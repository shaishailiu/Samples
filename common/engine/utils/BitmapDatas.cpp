#include "particle/ctrl/ColorTransition.h"
#include "BitmapDatas.h"


BitmapDatas::BitmapDatas(const int &w,const int &h,const unsigned int &color)
{
	//texinfo->texels = (GLubyte *)malloc (sizeof (GLubyte) * texinfo->width * texinfo->height * texinfo->internalFormat);
	width = w;
	height = h;
	format = GL_RGBA;
	int lg = width*height*4*sizeof(unsigned char);
	texels = new unsigned char[lg];
	int flag = 0;
	for(int i=0;i<height;i++){
		
		for(int j=0;j<width;j++){
			flag = (i * width + j)*4*sizeof(unsigned char);
			texels[flag]= (color>>16) & 0xFF;
			texels[flag+1] = (color>>8) & 0xFF;
			texels[flag+2] = (color) & 0xFF;
			texels[flag+3] =(color>>24) & 0xFF;
		}
	}
}


BitmapDatas::~BitmapDatas(void)
{
	if(texels != nullptr){
		delete texels;
		texels = nullptr;
	}
}

void BitmapDatas::setPixel( const unsigned int &xpos,const unsigned int &ypos,const unsigned int &color )
{
	if(xpos > width || ypos > height){
		return;
	}
	int flag = ((height - ypos - 1 ) * width + xpos) * 4;
	texels[flag]= (color>>16) & 0xFF;
	texels[flag+1] = (color>>8) & 0xFF;
	texels[flag+2] = (color) & 0xFF;
	texels[flag+3] =(color>>24) & 0xFF;
}

void BitmapDatas::setPixelByColorTransition( const ColorTransition &ct,const unsigned int &ypos )
{
	if(ct.width != width){
		return;
	}
	int yy = (height - ypos - 1 ) * width * 4;
	int flag;
	for(unsigned int i=0;i<width;i++){
		flag = ((height - ypos - 1 ) * width + i) * 4;
		texels[flag] = ct.data[i].X * 255;
		texels[flag+1] = ct.data[i].Y * 255;
		texels[flag+2] = ct.data[i].Z * 255;
		texels[flag+3] = ct.data[i].W * 255;
	}
}

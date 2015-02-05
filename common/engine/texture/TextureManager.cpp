//#include "../common/SimpleImageLoader.h"
#include <stdio.h>
#include "utils/PngUtil.h"
#include "utils/BitmapDatas.h"
#include "TextureManager.h"

using namespace std;

TextureManager::TextureManager(void)
{
	
}


TextureManager::~TextureManager(void)
{
}
/*
GLuint TextureManager::getTgaTexture(string fileUrl )
{
	
	SimpleImageLoader imgLoader;

	ImageObject *pImgObj;
	GLuint texId;

	pImgObj = imgLoader.LoadImageFile( fileUrl.c_str() );

	if ( pImgObj != NULL )
	{
		glGenTextures( 1, &texId );
		//glActiveTexture( GL_TEXTURE0 + texUnit );
		glBindTexture( GL_TEXTURE_2D, texId );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

		if ( pImgObj->GetNumChannels() == 3 )
		{
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, pImgObj->GetWidth(), pImgObj->GetHeight(),
				0, GL_RGB, GL_UNSIGNED_BYTE, pImgObj->GetDataPtr() );
		}
		else
		{
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, pImgObj->GetWidth(), pImgObj->GetHeight(),
				0, GL_RGBA, GL_UNSIGNED_BYTE, pImgObj->GetDataPtr() );
		}

		delete pImgObj;

		return texId;
	}
	
	return 0;
}
*/
GLuint TextureManager::getPngTexture(string fileUrl,bool repeat)
{
	if(hasCache(fileUrl)){
		return textureDic[fileUrl];
	}

	GLuint texId;

	PngUtil *texinfo = PngUtil::readPNGFromFile(fileUrl.c_str());
	//PngUtil *texinfo = PngUtil::readPNGBuffer(fileUrl.c_str());
	
	if ( texinfo != NULL )
	{
		glGenTextures( 1, &texId );
		
		//glActiveTexture( GL_TEXTURE0 + texUnit );
		glBindTexture( GL_TEXTURE_2D, texId );
		if(repeat){
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		}else{
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		}
		
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_L, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		if (texinfo->format == GL_RGB )
		{
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, texinfo->width, texinfo->height,
				0, GL_RGB, GL_UNSIGNED_BYTE, texinfo->texels);
		}
		else
		{
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texinfo->width, texinfo->height,
				0, GL_RGBA, GL_UNSIGNED_BYTE, texinfo->texels);
		}

		glGenerateMipmap(GL_TEXTURE_2D);

		//free(texinfo->texels);

		delete texinfo;

		textureDic.insert(make_pair(fileUrl,texId));

		return texId;
	}
	return 0;
}

bool TextureManager::hasCache( string &fileUrl )
{
	map<string,GLuint>::iterator it;
	it = textureDic.find(fileUrl);

	if(it == textureDic.end()){
		return false;
	}else {
		return true;
	}
}

GLuint TextureManager::getBitmapTexture(BitmapDatas *bmp,bool repeat )
{

	GLuint texId;

	glGenTextures( 1, &texId );
	//glActiveTexture( GL_TEXTURE0 + texUnit );
	glBindTexture( GL_TEXTURE_2D, texId );
	if(repeat){
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	}else{
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	}

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	if (bmp->format == GL_RGB )
	{
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, bmp->width, bmp->height,
			0, GL_RGB, GL_UNSIGNED_BYTE, bmp->texels);
	}
	else
	{
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, bmp->width, bmp->height,
			0, GL_RGBA, GL_UNSIGNED_BYTE, bmp->texels);
	}

		return texId;
	
	
}

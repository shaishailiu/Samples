#include "FileUtils.h"
#include "log/LogTrace.h"
#include <iostream>
#include <fstream>
#include "zlib/unzip.h"
#include <stdlib.h>
#include <string.h>

#if ANDROID
#include "assert.h"
#include "android/asset_manager.h"
#include "android/asset_manager_jni.h"
#endif

FileUtils::FileUtils(void)
{
}


FileUtils::~FileUtils(void)
{
}

#if ANDROID
/*
string FileUtils::readTxt( string fileUrl )
{
	//获取文件名并打开 
	const char *mfile = fileUrl.c_str();
	trace("read file");
	trace(mfile);
	AAsset* asset = AAssetManager_open(mgr, mfile,AASSET_MODE_UNKNOWN);  
	if(asset == NULL){
		trace("read error");
		return "";
	}else{
		//trace("read success");
	}
	//获取文件大小 
	off_t bufferSize = AAsset_getLength(asset);  
	
	char *buffer=(char *)malloc(bufferSize+1);  
	buffer[bufferSize]=0;  
	int numBytesRead = AAsset_read(asset, buffer, bufferSize);  
	
	string s = buffer;

	free(buffer);  
	//关闭文件
	AAsset_close(asset);  

	return s;
}
*/

static AAssetManager* mgr;

extern "C" {
	JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_initAsset(JNIEnv * env, jobject obj,jobject assetManager);
};

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_initAsset(JNIEnv * env, jobject obj,jobject assetManager){
	AAssetManager* assetmanager = AAssetManager_fromJava(env, assetManager);
	if (NULL == assetmanager) {
		trace("assetmanager : is NULL");
		return;
	}else{
		trace("assets init !");
	}
	mgr = assetmanager;
}

#endif

string FileUtils::readTxt( string fileUrl )
{
	
	Memory *memory = loadFile(fileUrl.c_str());

	string s((char*)(memory->buffer));

	delete memory;

	return s;
}




Memory * FileUtils::loadFile(const char *filename )
{
	//trace("load File:");
	//trace(filename);
#if WIN32
	Memory *memory = new Memory;

	FILE *fp;
	if((fp=fopen(filename,"rb"))==NULL){ 
		trace("can not find file");
		trace(filename);
		return NULL;
	}

	fseek(fp,0,SEEK_END);
	const long length=ftell(fp);
	fseek(fp,0,SEEK_SET);
	
	unsigned char *s = new unsigned char[length+1];

	fread(s,length,1,fp);

	memory->size = length;

	s[length] = 0;

	memory->buffer = s;

	fclose(fp);

	fp = NULL;
	
	return memory;
#elif IPHONE

	FILE *f;

	char fname[ MAX_PATH ] = {""};

	if( relative_path )
	{
		get_file_path( getenv( "FILESYSTEM" ), fname );

		strcat( fname, filename );
	}
	else strcpy( fname, filename );


	f = fopen( fname, "rb" );

	if( !f ) return NULL;


	Memory *memory = ( Memory * ) calloc( 1, sizeof( Memory ) );

	strcpy( memory->filename, fname );


	fseek( f, 0, SEEK_END );
	memory->size = ftell( f );
	fseek( f, 0, SEEK_SET );


	memory->buffer = ( unsigned char * ) calloc( 1, memory->size + 1 );
	fread( memory->buffer, memory->size, 1, f );
	memory->buffer[ memory->size ] = 0;


	fclose( f );

	return memory;


#elif ANDROID
	AAsset* asset = AAssetManager_open(mgr, filename,AASSET_MODE_UNKNOWN);  
	if(asset == NULL){
		trace("FileUtils loadFile error");
		trace(filename);
		return NULL;
	}else{
		//trace("read success");
	}
	/*获取文件大小*/  
	off_t bufferSize = AAsset_getLength(asset);  

	unsigned char *buffer= new unsigned char[bufferSize+1];  
	buffer[bufferSize]=0;  
	int numBytesRead = AAsset_read(asset, buffer, bufferSize);  

	Memory *memory = new Memory;

	memory->size = bufferSize;

	memory->buffer = buffer;
 
	/*关闭文件*/  
	AAsset_close(asset);  

	return memory;
#endif
}





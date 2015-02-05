#include "LogTrace.h"
#include <stdio.h>
#include <iostream>
#include <stdarg.h>
#include <string>

#if ANDROID
#include <android/log.h>
#define  LOG_TAG    "lyf"   //定义logcat中tag标签
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#endif

using namespace std;
/*
void trace(char *str){
	printf(str);
	printf("\n");
}
*/
void trace(unsigned int i){
	printf("%d\n",i);
}

void trace( const char *formatStr, ... )
{
#if	WIN32
	va_list params;
	char buf[4096];

	va_start ( params, formatStr );
	vsprintf_s ( buf, sizeof(buf),  formatStr, params );

	printf ( "%s\n", buf );
	
	va_end ( params ); 
#else
	//string s;
	//s = "tts";
    LOGI(formatStr);
#endif
}


void trace( int i )
{
#if WIN32
	printf("%d\n",i);
#else
	char t[256];
	sprintf(t, "%d", i);
	LOGI(t);
#endif
	
}

void trace(void *p){
	printf("%p\n",p);
}

void trace(const string &s )
{
	trace(s.c_str());
}

void trace( float f )
{
	printf("%f\n",f);
}

#if ANDROID
#include <jni.h>
#endif

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <string>

#include "log/LogTrace.h"
#include "engine/Engine.h"
#include "utils/Fps.h"
#include "game/GamePhone.h"


bool setupGraphics(int w, int h) {
	
	trace("start engine");
	trace(w);
	trace(h);
	Engine::getEngine()->start();

	Engine::getEngine()->resize(w,h);

	GamePhone::getGame()->init();

	return true;
}

void renderFrame() {
	GamePhone::getGame()->update();
}

void mouseDown(int x,int y) {
	GamePhone::getGame()->mouseDownHander(x,y);
}

void mouseMove(int x,int y) {
	GamePhone::getGame()->mouseMoveHander(x,y);
}

void mouseUp(int x,int y) {
	GamePhone::getGame()->mouseUpHander(x,y);
}

char *fpsbuffer=new char[30];

char * getFps(){
	sprintf( fpsbuffer , "fps:%d",Fps::frame);
	return fpsbuffer;
	
}

#if ANDROID
extern "C" {
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj);
	JNIEXPORT jstring JNICALL Java_com_android_gl2jni_GL2JNILib_info(JNIEnv * env, jobject obj);

	JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_toucheBegan(JNIEnv * env, jobject obj, jfloat x, jfloat y);
	JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_toucheMoved(JNIEnv * env, jobject obj, jfloat x, jfloat y);
	JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_toucheEnded(JNIEnv * env, jobject obj, jfloat x, jfloat y);
};

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj)
{
    renderFrame();
}

JNIEXPORT jstring JNICALL Java_com_android_gl2jni_GL2JNILib_info(JNIEnv * env, jobject obj)
{
	//char *buffer=new char[30];
	//sprintf( buffer , "fps:%d",getFps());
	return env->NewStringUTF(getFps());
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_toucheBegan(JNIEnv * env, jobject obj, jfloat x, jfloat y)
{
	//char *buffer=new char[30];
	//sprintf( buffer , "begin:%f+%f", x,y);
	//trace(buffer);

	mouseDown(int(x),int(y));
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_toucheMoved(JNIEnv * env, jobject obj, jfloat x, jfloat y)
{
	//char *buffer=new char[30];
	//sprintf( buffer , "move:%f+%f", x,y);
	//trace(buffer);
	mouseMove(int(x),int(y));
}
JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_toucheEnded(JNIEnv * env, jobject obj, jfloat x, jfloat y)
{
	//char *buffer=new char[30];
	//sprintf( buffer , "end:%f+%f", x,y);
	//trace(buffer);
	mouseUp(int(x),int(y));
}

#endif


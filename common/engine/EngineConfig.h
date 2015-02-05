#ifndef _ENGINECONFIG_H_
#define _ENGINECONFIG_H_

#if ANDROID
#define PERROOT "data/"
#else
#define PERROOT "./data/"
#endif

#define MAXVALUE 200000000;
#define FRAMETIME 16.66666667;



struct EngineConfig
{
	int width;
	int height;
	int mapWidth;
	int mapHeight;

	float frameTime;
};

#endif


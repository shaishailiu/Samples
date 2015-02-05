#include <time.h>
#if ANDROID
#include <sys/time.h>
#else
#include <windows.h>
#endif

#include "TimeUtil.h"


TimeUtil::TimeUtil(void)
{
}


TimeUtil::~TimeUtil(void)
{
}
#if ANDROID
unsigned int TimeUtil::getTimer()
{
	uint uptime = 0;
	struct timeval tv;   
	gettimeofday(&tv, NULL);   
	uptime = tv.tv_sec*1000 + tv.tv_usec/1000;
	return uptime;
}
#else
unsigned int TimeUtil::getTimer()
{

	struct timeval tv;

	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);

	tm.tm_year     = wtm.wYear - 1900;
	tm.tm_mon     = wtm.wMonth - 1;
	tm.tm_mday     = wtm.wDay;
	tm.tm_hour     = wtm.wHour;
	tm.tm_min     = wtm.wMinute;
	tm.tm_sec     = wtm.wSecond;
	tm. tm_isdst    = -1;
	clock = mktime(&tm);

	tv.tv_sec = clock;
	tv.tv_usec = wtm.wMilliseconds;

	unsigned int result = tv.tv_sec * 1000 + tv.tv_usec;

	return result;
}
#endif

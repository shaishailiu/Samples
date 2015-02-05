#ifndef _LOGTRACE_H_
#define _LOGTRACE_H_

#include <string>

void trace( const char *formatStr, ... );
void trace(unsigned int i);
void trace(int i);
void trace(void *p);
void trace(float f);

//void trace(const string &s);

#endif
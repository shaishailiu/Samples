#ifndef __BindAttrib_h__
#define __BindAttrib_h__
#include <string>

using namespace std;

class BindAttrib
{
public:
	BindAttrib(void);
	~BindAttrib(void);
	int bindID;
	string bindattribute;
};

#endif
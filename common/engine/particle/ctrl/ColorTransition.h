#ifndef _COLORTRANSITION_H_
#define _COLORTRANSITION_H_

#include "json/json.h"
#include "math/Vector.h"

class ColorTransition
{
public:
	ColorTransition(void);
	~ColorTransition(void);

	Vector5 data[64];

	int hasData;//1Ϊ������ -1Ϊ������

	unsigned int width;

	void setDataByJson(const Json::Value &colorData,const bool &isShuffle);
	void swap(Vector5 &vc1,Vector5 &vc2);

};

#endif
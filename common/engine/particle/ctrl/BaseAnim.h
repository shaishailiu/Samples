#ifndef _BASEANIM_H_
#define _BASEANIM_H_

#include <vector>
#include <string>
#include "particle/TypeValue.h"

class BaseAnim
{
public:
	BaseAnim(void);
	~BaseAnim(void);

	float baseNum;
	float num;
	int time;
	float speed;
	float aSpeed;
	int beginTime;
	int lastTime;
	float baseTime;
	bool _isActiva;
	bool isDeath;

	virtual void update(const int t);
	virtual void coreCalculate();
	void reset();
	void depthReset();
	virtual void setData(const std::vector<TypeValue> ary);
	virtual void getAllNum(float allTime);

	float string2f(const std::string str);
	void string2Ary(const std::string str,float num[]);
	
};

#endif
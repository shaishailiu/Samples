#ifndef _SCALENOISE_H_
#define _SCALENOISE_H_

#include "baseanim.h"
#include <vector>
#include "particle/TypeValue.h"

class ScaleNoise :
	public BaseAnim
{
public:
	ScaleNoise(void);
	~ScaleNoise(void);

	float amplitude;

	virtual void coreCalculate();
	virtual void setData(const std::vector<TypeValue> ary);
	virtual void getAllNum(float allTime);
};

#endif
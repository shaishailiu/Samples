#ifndef _SCALECHANGE_H_
#define _SCALECHANGE_H_

#include "baseanim.h"
#include <vector>
#include "particle/TypeValue.h"

class ScaleChange :
	public BaseAnim
{
public:
	ScaleChange(void);
	~ScaleChange(void);

	float maxNum;
	float minNum;

	virtual void coreCalculate();

	virtual void getAllNum(float allTime);

	virtual void setData(const std::vector<TypeValue> ary);
};

#endif
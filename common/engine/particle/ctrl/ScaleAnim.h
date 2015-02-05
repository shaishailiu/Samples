#ifndef _SCALEANIM_H_
#define _SCALEANIM_H_

#include "baseanim.h"
#include "ScaleAnimObj.h"
#include <vector>
#include "particle/TypeValue.h"

class ScaleAnim :
	public BaseAnim
{
public:
	ScaleAnim(void);
	~ScaleAnim(void);

	std::vector<ScaleAnimObj*> scaleAry;
	float beginScale;
	int scaleNum;
	ScaleAnimObj *_currentTarget;
	int flag;

	virtual void update(const int t);
	virtual void coreCalculate();
	virtual void setData(const std::vector<TypeValue> ary);
	virtual void getAllNum(float allTime);

};

#endif
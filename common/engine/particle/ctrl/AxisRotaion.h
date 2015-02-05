#ifndef _AXISROTAION_H_
#define _AXISROTAION_H_

#include "BaseAnim.h"
#include <vector>
#include "particle/TypeValue.h"
#include "math/Vector.h"


class AxisRotaion :
	public BaseAnim
{
public:
	AxisRotaion(void);
	~AxisRotaion(void);
	
	Vector3 axis;
	Vector3 axisPos;

	virtual void setData(const std::vector<TypeValue> ary);
};

#endif
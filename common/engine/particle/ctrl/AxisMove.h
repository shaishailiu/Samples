#ifndef _AXISMOVE_H_
#define _AXISMOVE_H_

#include "baseanim.h"
#include <vector>
#include "particle/TypeValue.h"
#include "math/Vector.h"

class AxisMove :
	public BaseAnim
{
public:
	AxisMove(void);
	~AxisMove(void);

	Vector3 axis;

	virtual void setData(const std::vector<TypeValue> ary);
};

#endif
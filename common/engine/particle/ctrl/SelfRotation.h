#ifndef _SELFROTATION_H_
#define _SELFROTATION_H_

#include "baseanim.h"
class SelfRotation :
	public BaseAnim
{
public:
	SelfRotation(void);
	~SelfRotation(void);

	virtual void setData(const std::vector<TypeValue> ary);
};

#endif
#ifndef _UNITTESTING_H_
#define _UNITTESTING_H_

#include "thread/TestThread.h"

class UnitTesting
{
public:
	UnitTesting();
	~UnitTesting();

	TestThread thread;

	void init();
};

#endif // !_UNITTESTING_H_


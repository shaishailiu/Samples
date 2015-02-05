#ifndef _INTERACTIVEINPUT_H_
#define _INTERACTIVEINPUT_H_

#include "math/Core.h"

class InteractiveInput
{
public:
	InteractiveInput();
	~InteractiveInput();

	int stateType;
	bool bRightMouseDown;

	Vector2 mousePos;

	void leftMouseDown(int x, int y);
	void leftMouseUp(int x, int y);

	void mouseMove(int x, int y);

	void rightMouseDown(int x, int y);
	void rightMouseUp(int x, int y);

	void mouseWheel(int delta);

};

#endif
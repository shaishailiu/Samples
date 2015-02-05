#include "Engine.h"
#include "utils/Camera3D.h"
#include "InteractiveInput.h"


InteractiveInput::InteractiveInput()
{
	bRightMouseDown = false;
}


InteractiveInput::~InteractiveInput()
{
}

void InteractiveInput::leftMouseDown(int x, int y)
{

}

void InteractiveInput::leftMouseUp(int x, int y)
{

}

void InteractiveInput::mouseMove(int x, int y)
{
	if (bRightMouseDown)
	{
		Engine::getCamera()->setAngleX(Engine::getCamera()->getAngleX() + (float(x) - mousePos.X) * 0.1);
		Engine::getCamera()->setAngleY(Engine::getCamera()->getAngleY() + (float(y) - mousePos.Y) * 0.1);
		mousePos.set(x, y);
	}
}

void InteractiveInput::rightMouseDown(int x, int y)
{
	bRightMouseDown = true;
	mousePos.set(x, y);
}

void InteractiveInput::rightMouseUp(int x, int y)
{
	bRightMouseDown = false;
}

void InteractiveInput::mouseWheel(int delta)
{
	Engine::getCamera()->addDistance(float(delta)*0.03);
}

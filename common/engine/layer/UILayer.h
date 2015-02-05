#ifndef _UILAYER_H_
#define _UILAYER_H_

#include "baselayer.h"
#include <vector>

class Display3dUI;

class UILayer :
	public BaseLayer
{
public:
	UILayer(void);
	~UILayer(void);

	virtual void update();
	void addChild(Display3dUI *ui);
	void addChildAt(Display3dUI *ui,const int index);
	void setChildIndex(Display3dUI *ui,const int index);

	void removeChild(Display3dUI *ui);
	void removeChildAt(const int index);

	Display3dUI * getChildAt(const int index);
	int getChildIndex(Display3dUI *ui);

	std::vector<Display3dUI*> uilist;
private:
	void regShaer();
};

#endif

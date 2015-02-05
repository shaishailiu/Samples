#ifndef _UICONTROL_H_
#define _UICONTROL_H_

class Display3dUI;
class Vector2;

class UIControl
{
public:
	UIControl(void);
	~UIControl(void);
	void initUI();

	void mouseDown(const int x,const int y);
	void mouseMove(const int x,const int y);
	void mouseUp();

	void stopMove();


	Display3dUI *directionBtn;
	Display3dUI *directionBgBtn;
	Display3dUI *attackBtn;

	Display3dUI *skill1;
	Display3dUI *skill2;
	Display3dUI *skill3;

	CombineParticle *cp;
	CombineParticle *cp2;
	CombineParticle *cp3;
	CombineParticle *cp4;

	CombineParticle *cp5;

	Display3dUI * getUI(string name,string upName,float w,float h,float x,float y,float rx,float ry);
	Vector2 basePos;
	bool isDrag;
};

#endif


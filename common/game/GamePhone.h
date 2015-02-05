#ifndef _GAMEPHONE_H_
#define _GAMEPHONE_H_

class Display3dMovie;
class UIControl;
class CombineParticle;

class GamePhone
{
public:
	static GamePhone *getGame();
	static Display3dMovie *getMainChar();

	void init();
	void update();
	void keyHander(const bool key[]);
	void mouseDownHander(int x,int y);
	void mouseMoveHander(int x,int y);
	void mouseUpHander(int x,int y);
protected:

	Display3dMovie *mainChar;

	UIControl *uiControl;

	//CombineParticle *cp;

	GamePhone(void);
	~GamePhone(void);

private:

	Display3dMovie *getMonsterChar();

};

#endif
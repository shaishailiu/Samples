#ifndef _FPS_H
#define _FPS_H

class Fps
{
public:
	Fps(void);
	~Fps(void);

	static int frame;
	static int time;
	static int num;

	static void addTime(int t);
};

#endif
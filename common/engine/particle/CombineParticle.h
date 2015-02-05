#ifndef _COMBINEPARTICLE_H_
#define _COMBINEPARTICLE_H_

#include <string>
#include <vector>

class Display3D;

class Display3dParticle;

class CombineParticle
{
public:
	CombineParticle(void);
	~CombineParticle(void);

	std::vector<Display3dParticle*> displayVec;

	void update();

	void updateTime(const int t);

	void load(const std::string url);

	void reset(const int t);

	void setBindTarget(Display3D *display);

private:

	int _time;
	int _maxTime;

	void setMaxNum();

};

#endif
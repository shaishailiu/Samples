#ifndef _PARTICLEMANAGER_H_
#define _PARTICLEMANAGER_H_

#include <string>
#include <vector>

class CombineParticle;

class ParticleManager
{
public:
	ParticleManager(void);
	~ParticleManager(void);

	std::vector<CombineParticle *> particleList;

	CombineParticle *loadParticle(const std::string url);

	void addParticle(CombineParticle *cp);

	void removeParticle(CombineParticle *cp);

	void updateTime(const int t);

	void update();
};

#endif
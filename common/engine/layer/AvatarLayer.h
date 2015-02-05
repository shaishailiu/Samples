#ifndef _AVATARLAYER_H_
#define _AVATARLAYER_H_

#include <vector>
#include "BaseLayer.h"

class Display3dMovie;

class AvatarLayer : public BaseLayer
{
public:
	AvatarLayer(void);
	~AvatarLayer(void);

	virtual void update();

	void updateShadow();

	void upateTime(int $time);

	void addAvatar(Display3dMovie *mc);

	Display3dMovie *display3dMovie;
private:
	void regShaer();
	std::vector<Display3dMovie*> _avatarList;
};

#endif

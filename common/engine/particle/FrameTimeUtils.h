#ifndef _FRAMETIMEUTILS_H_
#define _FRAMETIMEUTILS_H_

#include <vector>
#include "ParticleAnimVo.h"
#include "ctrl/SelfRotation.h"
#include "ctrl/AxisRotaion.h"
#include "ctrl/Centrifugal.h"
#include "ctrl/AxisMove.h"
#include "ctrl/ColorChange.h"
#include "ctrl/ScaleChange.h"
#include "ctrl/ScaleAnim.h"
#include "ctrl/ScaleNoise.h"

class FrameTimeUtils
{
public:
	FrameTimeUtils(void);
	~FrameTimeUtils(void);

	SelfRotation _selfRotaion;
	AxisRotaion _axisRotaion;
	Centrifugal _centrifugal;
	AxisMove _axisMove;
	ColorChange _colorChange;
	ScaleChange _scaleChange;
	ScaleAnim _scaleAnim;
	ScaleNoise _scaleNosie;

	void process(std::vector<ParticleAnimVo> &timeline);

	void reset();

};

#endif
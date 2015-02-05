#include <math.h>
#include "EngineConfig.h"
#include "ScaleNoise.h"


ScaleNoise::ScaleNoise(void)
{
}


ScaleNoise::~ScaleNoise(void)
{
}

void ScaleNoise::coreCalculate()
{
	num = amplitude + amplitude * sin(speed*time);
}

void ScaleNoise::setData( const std::vector<TypeValue> ary )
{
	beginTime = string2f(ary[0].value);
	if(string2f(ary[1].value) == -1){
		lastTime = MAXVALUE;
	}else{
		lastTime = string2f(ary[1].value);
	}
	amplitude = string2f(ary[2].value);
	speed = string2f(ary[3].value)*0.01;
}

void ScaleNoise::getAllNum( float allTime )
{
	baseNum = amplitude + amplitude * sin(speed*allTime);
}

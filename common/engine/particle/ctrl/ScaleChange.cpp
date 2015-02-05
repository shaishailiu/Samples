#include "ScaleChange.h"
#include "EngineConfig.h"

ScaleChange::ScaleChange(void)
{
	num = 1;
}


ScaleChange::~ScaleChange(void)
{
}

void ScaleChange::setData( const std::vector<TypeValue> ary )
{
	beginTime = string2f(ary[0].value);
	if(string2f(ary[1].value) == -1){
		lastTime = MAXVALUE;
	}else{
		lastTime = string2f(ary[1].value);
	}
	speed = string2f(ary[2].value)*0.001;
	minNum = string2f(ary[3].value)*0.01;
	maxNum = string2f(ary[4].value)*0.01;
}

void ScaleChange::coreCalculate()
{
	num = 1+speed*time + baseNum;
	if(num < minNum){
		num = minNum;
	}else if(num > maxNum){
		num = maxNum;
	}
}

void ScaleChange::getAllNum( float allTime )
{
	if(allTime > lastTime){
		allTime = lastTime;
	}
	allTime = allTime - beginTime;

	float n = speed*allTime;
	baseNum += n;
	if(baseNum < minNum){
		baseNum = minNum;
	}else if(n > maxNum){
		baseNum = maxNum;
	}
}

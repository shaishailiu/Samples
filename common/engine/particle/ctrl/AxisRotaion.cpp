#include "AxisRotaion.h"
#include "EngineConfig.h"

AxisRotaion::AxisRotaion(void)
{
}


AxisRotaion::~AxisRotaion(void)
{
}

void AxisRotaion::setData(const std::vector<TypeValue> ary )
{
	beginTime = string2f(ary[0].value);
	if(string2f(ary[1].value) == -1){
		lastTime = MAXVALUE;
	}else{
		lastTime = string2f(ary[1].value);
	}
	float vc[5];
	string2Ary(ary[2].value,vc);
	axis.set(vc[0],vc[1],vc[2]);

	string2Ary(ary[3].value,vc);
	axisPos.set(vc[0]*100,vc[1]*100,vc[2]*100);

	speed = string2f(ary[4].value)*0.1;
	aSpeed = string2f(ary[5].value)*0.1;
	
}

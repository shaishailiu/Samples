#include "AxisMove.h"
#include "EngineConfig.h"


AxisMove::AxisMove(void)
{
}


AxisMove::~AxisMove(void)
{
}

void AxisMove::setData( const std::vector<TypeValue> ary )
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
	axis.normalize();


	speed = string2f(ary[3].value)*0.1;
	aSpeed = string2f(ary[4].value)*0.001;
}



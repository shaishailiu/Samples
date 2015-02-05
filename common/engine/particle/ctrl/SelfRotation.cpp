#include "SelfRotation.h"
#include "EngineConfig.h"


SelfRotation::SelfRotation(void)
{
}


SelfRotation::~SelfRotation(void)
{
}

void SelfRotation::setData( const std::vector<TypeValue> ary )
{
	beginTime = string2f(ary[0].value);
	if(string2f(ary[1].value) == -1){
		lastTime = MAXVALUE;
	}else{
		lastTime = string2f(ary[1].value);
	}
	speed = string2f(ary[2].value)*0.1;
	aSpeed = string2f(ary[3].value)*0.1;
}

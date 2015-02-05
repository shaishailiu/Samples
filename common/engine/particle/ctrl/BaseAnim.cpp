#include "BaseAnim.h"


BaseAnim::BaseAnim(void)
{

	baseNum = 0;
	num=0;
	time = 0;
	speed=0;
	aSpeed=0;
	beginTime = 0;
	lastTime = 0;
	baseTime = 0;
	_isActiva = false;
	isDeath = false;
}


BaseAnim::~BaseAnim(void)
{
}

void BaseAnim::update( const int t )
{
	if(isDeath){
		return;
	}
	time = t - baseTime;
	if(_isActiva){
		time = time-beginTime;
		if(time > lastTime){
			time = lastTime - beginTime;
			isDeath = true;
		}
		coreCalculate();
	}else{
		if(time >= beginTime){
			if(time >= lastTime){
				time = lastTime - beginTime;
				coreCalculate();
				isDeath = true;
			}else{
				time = time-beginTime;
				coreCalculate();
			}
			_isActiva = true;
		}
	}
}

void BaseAnim::coreCalculate()
{
	num = speed*time + aSpeed*time*time + baseNum;
}

void BaseAnim::reset()
{
	_isActiva = false;
	isDeath = false;
	num = 0;
}

void BaseAnim::depthReset()
{
	_isActiva = false;
	isDeath = false;

	time = 0;
	baseNum = 0;
	num = 0;
}


void BaseAnim::getAllNum( float allTime )
{
	//allTime = Math.min(allTime,lastTime);
	if(allTime > lastTime){
		allTime = lastTime;
	}
	allTime = allTime - beginTime;
	float n = speed*allTime + aSpeed*allTime*allTime;
	baseNum += n;
}

void BaseAnim::setData(const std::vector<TypeValue> ary )
{

}

float BaseAnim::string2f( const std::string str )
{
	return atof(str.c_str());
}

void BaseAnim::string2Ary( const std::string str,float num[] )
{
	//char *s = str.c_str();
	char *s = const_cast<char*>(str.c_str());
	const char *d = "|";
	char *p;
	p = strtok(s,d);
	int i = 0;
	while(p)
	{
		num[i] = atof(p);
		p=strtok(NULL,d);
		i++;
	}

}

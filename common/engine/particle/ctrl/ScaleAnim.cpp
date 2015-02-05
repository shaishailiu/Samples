#include "ScaleAnim.h"
#include "EngineConfig.h"


ScaleAnim::ScaleAnim(void)
{
	flag = 0;
}


ScaleAnim::~ScaleAnim(void)
{
	for(unsigned int i=0;i<scaleAry.size();i++){
		delete scaleAry[i];
	}
}

void ScaleAnim::update( const int t )
{
	if(isDeath){
		return;
	}
	time = t - baseTime;
	if(_isActiva){
		coreCalculate();
		if(time > lastTime){
			isDeath = true;
		}
	}else{
		if(time >= beginTime){
			_isActiva = true;
		}
	}
}

void ScaleAnim::coreCalculate()
{
	if(time>_currentTarget->beginTime){//ÇÐ»»½×¶Î
		beginTime = _currentTarget->beginTime;
		beginScale = _currentTarget->value;
		flag++;
		if(flag == scaleAry.size()){
			isDeath = true;
			return;
		}
		_currentTarget = scaleAry[flag];
	}
	num = (_currentTarget->value-beginScale)/_currentTarget->time*(time-beginTime) + beginScale;
}

void ScaleAnim::setData( const std::vector<TypeValue> ary )
{
	beginTime = string2f(ary[0].value);
	if(string2f(ary[1].value) == -1){
		lastTime = MAXVALUE;
	}else{
		lastTime = string2f(ary[1].value);
	}
	beginScale = string2f(ary[2].value);
	scaleNum = string2f(ary[3].value);

	
	
	int addTime=0;
	for(int i = 4;i<4+scaleNum*2;i+=2){
		ScaleAnimObj *obj = new ScaleAnimObj;
		obj->value = string2f(ary[i].value);
		obj->time = string2f(ary[i+1].value);
		addTime += obj->time;
		obj->beginTime = beginTime + addTime;
		scaleAry.push_back(obj);
	}

	_currentTarget = scaleAry[0];
	
}

void ScaleAnim::getAllNum( float allTime )
{
	//allTime = Math.min(allTime,lastTime+beginTime);
	if(allTime > (lastTime+beginTime)){
		allTime = lastTime+beginTime;
	}

	ScaleAnimObj *target = scaleAry[scaleAry.size()-1];
	if(allTime >= (target->beginTime+target->time)){
		baseNum = target->value;
		return;
	}

	int flag;
	for(int i=0;i<scaleAry.size();i++){
		if(allTime > scaleAry[i]->beginTime){
			_currentTarget = scaleAry[i];
			beginTime = _currentTarget->beginTime;
			beginScale = _currentTarget->value;
			flag = i;
		}
	}

	flag++;
	_currentTarget = scaleAry[flag];

	baseNum = (_currentTarget->value-beginScale)/_currentTarget->time*(allTime-beginTime) + beginScale;
}

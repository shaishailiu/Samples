#include "math/MathUtils.h"
#include "ColorTransition.h"
#include "log/LogTrace.h"


ColorTransition::ColorTransition(void)
{
	width = 64;
	hasData = -1;
}


ColorTransition::~ColorTransition(void)
{
}

void ColorTransition::setDataByJson( const Json::Value &colorData ,const bool &isShuffle)
{
	//从json读取数据
	int s = colorData["alpha"].size();

	if(s == 0){
		hasData = -1;
		return;
	}

	std::vector<Vector5> ary;

	unsigned int i;
	bool hasdataflag = true;
	for(i=0;i<s;i++){
		Vector5 v;
		int color = colorData["color"][i].asInt();
		v.X = (color>>16) & 0xFF;
		v.Y = (color>>8) & 0xFF;
		v.Z = (color) & 0xFF; 
		v.W = colorData["alpha"][i].asDouble();
		v.P = colorData["pos"][i].asDouble();
		if(color != 16581375){
			hasdataflag = false;
		}
		if(v.W != 1){
			hasdataflag = false;
		}

		ary.push_back(v);
	}
	if(hasdataflag){
		hasData = -1;
	}else{
		hasData = 1;
	}
	//写入最终颜色值
	if(ary.size() == 1){
		for(i=0;i<64;i++){
			data[i] = ary[0];
		}
		return;
	}

	float *key = new float[ary.size()];
	for(i=0;i<ary.size();i++){
		key[i] = ary[i].P/255 * 64;
	}
	
	int index = 0;
	int flag = key[index];

	for(i=0;i<64;i++){
		if(i >= flag){
			index++;
			flag = key[index];
		}

		Vector5 *first;
		Vector5 *second;

		if(index == 0){
			first = &(ary[index]);
			second = &(ary[index]);
		}else if(index >= ary.size()){
			first = &(ary[index-1]);
			second = &(ary[index-1]);
		}else{
			first = &(ary[index-1]);
			second = &(ary[index]);
		}

		float per = 0;
		if(first->P != second->P){
			per = ((i/64.0f) - (first->P/255))/((second->P - first->P)/255);
		}

		data[i].X = (second->X * per + first->X * (1-per))/255;
 		data[i].Y = (second->Y * per + first->Y * (1-per))/255;
		data[i].Z = (second->Z * per + first->Z * (1-per))/255;
		data[i].W = (second->W * per + first->W * (1-per));
	}

	delete key;

	if(isShuffle){
		for(i=0;i<64;i++){
			int index = 64 * random();
			swap(data[index],data[0]);
		}
	}
	
}

void ColorTransition::swap( Vector5 &vc1,Vector5 &vc2 )
{
	Vector5 vc;
	vc.set(vc1.X,vc1.Y,vc1.Z,vc1.W,vc1.P);

	vc1.set(vc2.X,vc2.Y,vc2.Z,vc1.W,vc2.P);

	vc2.set(vc.X,vc.Y,vc.Z,vc1.W,vc.P);
}

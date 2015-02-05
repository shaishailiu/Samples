#include "Fps.h"


int Fps::frame = 0;
int Fps::time = 0;
int Fps::num = 0;

Fps::Fps(void)
{

}

Fps::~Fps(void)
{
}

void Fps::addTime( int t )
{
	time += t;
	num++;
	if(time >= 1000){
		frame = num;
		time = 0;
		num = 0;
	}
}

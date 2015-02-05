#ifndef _MATHUTILS_H_
#define _MATHUTILS_H_

#define random() ((rand()%100)/100.0f)
#define PI 3.1415926

#define angle2Radian(angle) (angle * PI / 180.0f)
//float angle2Radian(float angle){
//	return angle * PI / 180.0f;
//}
#define radian2Angle(radian) (radian *  180.0f / PI)
//float radian2Angle(float radian){
//	return radian *  180.0f / PI;
//}

#endif

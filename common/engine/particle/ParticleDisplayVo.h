#ifndef _PARTICLEDISPLAYVO_H_
#define _PARTICLEDISPLAYVO_H_

#include <string>
#include <vector>
#include "math/Vector.h"
#include "json/json.h"
#include "ctrl/ColorTransition.h"

class ParticleDisplayVo
{
public:
	ParticleDisplayVo(void);
	~ParticleDisplayVo(void);

	int particleType;
	/**************************/
	float width;//宽
	float height;//高
	bool tileMode;//紧贴表面
	bool widthFixed;//宽度比例不变
	bool heightFixed;//高度比例不变
	float originWidthScale;//原点宽度比例
	float originHeightScale;//原点高度比例
	bool isCycle;//是否循环
	float speed;// 速度
	float uSpeed;//u坐标平移速度
	float vSpeed;//v坐标平移速度
	std::string textureUrl;//贴图路径
	std::string maskUrl;//遮罩贴图路径
	int renderPriority;//渲染优先级
	int animLine;//动画行数
	int animRow;//动画列数 
	int animInterval;//动画时间间隔
	int eyeDistance;//距离视点距离
	int alphaMode;//alpha混合模式
	int life;//生命长度
	bool watchEye;//是否面向视点
	bool closeGround;//紧贴地面
	bool gormalsGround;//使用地面法线
	

	bool isU;//u翻转
	bool isV;//v翻转
	bool isUV;//uv翻转


	float rotationX;
	float rotationY;
	float rotationZ;

	Vector3	center;
	float overAllScale;
	

	/**************************/
	int totalNum;//   粒子配额
	float acceleration;//加速度
	float toscale;// 大小变化
	bool timeRandom;//是否随机  发射随机
	float qishijuli;
	bool lockY;//锁定y轴
	bool lockX;//锁定x轴
	bool isLoop;//是否循环
	Vector4 shootAngly;// 发射角度
	float shootSpeed;//发射速率
	float shootInterval;//间隔时间
	bool isRandom;//是否随机  起点随机
	bool isSendRandom;//是否随机发射速度
	bool isSendAngleRandom;//是否随机发射角度
	Vector4 ziZhuanAngly;
	Vector4 addforce;
	Vector4 lixinForce;
	Vector4 waveform;
	Vector4 round;//初始位置
	bool is3Dlizi;
	float gezhiDuanshu;
	bool closeSurface;//紧贴表面
	bool isEven;
	Vector3 basePositon;
	float baseRandomAngle;
	int shapeType;
	int fasanJiaodu;
	float paticleMinScale;
	float paticleMaxScale;
	bool islixinAngly;
	Vector3 particleRandomScale;


	int fenduanshu;//分段数
	float qingxiejiaodu;//倾斜角度
	bool isCenter;

	/**************************/
	float widthScale;//宽度缩放
	int faceNum;//面数

	/**************************/
	int maxAnimTime;//最大动画时间


	/**************************/
	std::string objUrl;//模型路径
	float objScale;//模型缩放比例

	/**************************/
	Vector3 beginVector3D;
	Vector3 endVector3D;
	int density;

	/**************************/
	std::string meshUrl;//mesh路径
	std::string animUrl;//anim路径
	bool depthMode;//开启深度测试
	float playSpeed;//播放速度

	ColorTransition randomColor;
	ColorTransition textureColor;
	std::vector<std::string> data;
	
	
	float segmentnum;
	float segmentspeed;
	float endwidth;
	int isBack;

	void setDataByJson(const Json::Value vo);
	Vector4 getVec4(const Json::Value v4d);
	Vector3 getVec3(const Json::Value v3d);
};

#endif
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
	float width;//��
	float height;//��
	bool tileMode;//��������
	bool widthFixed;//��ȱ�������
	bool heightFixed;//�߶ȱ�������
	float originWidthScale;//ԭ���ȱ���
	float originHeightScale;//ԭ��߶ȱ���
	bool isCycle;//�Ƿ�ѭ��
	float speed;// �ٶ�
	float uSpeed;//u����ƽ���ٶ�
	float vSpeed;//v����ƽ���ٶ�
	std::string textureUrl;//��ͼ·��
	std::string maskUrl;//������ͼ·��
	int renderPriority;//��Ⱦ���ȼ�
	int animLine;//��������
	int animRow;//�������� 
	int animInterval;//����ʱ����
	int eyeDistance;//�����ӵ����
	int alphaMode;//alpha���ģʽ
	int life;//��������
	bool watchEye;//�Ƿ������ӵ�
	bool closeGround;//��������
	bool gormalsGround;//ʹ�õ��淨��
	

	bool isU;//u��ת
	bool isV;//v��ת
	bool isUV;//uv��ת


	float rotationX;
	float rotationY;
	float rotationZ;

	Vector3	center;
	float overAllScale;
	

	/**************************/
	int totalNum;//   �������
	float acceleration;//���ٶ�
	float toscale;// ��С�仯
	bool timeRandom;//�Ƿ����  �������
	float qishijuli;
	bool lockY;//����y��
	bool lockX;//����x��
	bool isLoop;//�Ƿ�ѭ��
	Vector4 shootAngly;// ����Ƕ�
	float shootSpeed;//��������
	float shootInterval;//���ʱ��
	bool isRandom;//�Ƿ����  ������
	bool isSendRandom;//�Ƿ���������ٶ�
	bool isSendAngleRandom;//�Ƿ��������Ƕ�
	Vector4 ziZhuanAngly;
	Vector4 addforce;
	Vector4 lixinForce;
	Vector4 waveform;
	Vector4 round;//��ʼλ��
	bool is3Dlizi;
	float gezhiDuanshu;
	bool closeSurface;//��������
	bool isEven;
	Vector3 basePositon;
	float baseRandomAngle;
	int shapeType;
	int fasanJiaodu;
	float paticleMinScale;
	float paticleMaxScale;
	bool islixinAngly;
	Vector3 particleRandomScale;


	int fenduanshu;//�ֶ���
	float qingxiejiaodu;//��б�Ƕ�
	bool isCenter;

	/**************************/
	float widthScale;//�������
	int faceNum;//����

	/**************************/
	int maxAnimTime;//��󶯻�ʱ��


	/**************************/
	std::string objUrl;//ģ��·��
	float objScale;//ģ�����ű���

	/**************************/
	Vector3 beginVector3D;
	Vector3 endVector3D;
	int density;

	/**************************/
	std::string meshUrl;//mesh·��
	std::string animUrl;//anim·��
	bool depthMode;//������Ȳ���
	float playSpeed;//�����ٶ�

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
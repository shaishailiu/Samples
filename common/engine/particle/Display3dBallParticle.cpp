#include <string>
#include <vector>
#include "utils/BindAttrib.h"
#include "vo/ObjData.h"
#include "vo/ParticleBallData.h"
#include "Engine.h"
#include "EngineConfig.h"
#include "utils/Camera3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils/BitmapDatas.h"
#include "particle/ctrl/ColorTransition.h"
#include "Engine.h"
#include "texture/TextureManager.h"
#include "math/MathUtils.h"

#include "Display3dBallParticle.h"

//#define random() ((rand()%100)/100.0f)

using namespace std;

Display3dBallParticle::Display3dBallParticle(void)
{
	objData = new ParticleBallData();
	currentFrame = 0;
	watchMatrix = new Matrix;
}


Display3dBallParticle::~Display3dBallParticle(void)
{
	if(objData != nullptr){
		delete objData;
		objData = nullptr;
	}
	if(watchMatrix != nullptr){
		delete watchMatrix;
		watchMatrix = nullptr;
	}
}

vector<BindAttrib> Display3dBallParticle::getBindAtt()
{
	vector<BindAttrib> vec;

	BindAttrib bind0;
	bind0.bindID=0;
	bind0.bindattribute="vPosition";
	vec.push_back(bind0);


	BindAttrib bind1;
	bind1.bindID=1;
	bind1.bindattribute="texcoord";
	vec.push_back(bind1);

	BindAttrib bind2;
	bind2.bindID=2;
	bind2.bindattribute="basePos";
	vec.push_back(bind2);

	BindAttrib bind3;
	bind3.bindID=3;
	bind3.bindattribute="speed";
	vec.push_back(bind3);

	return vec;
}

string Display3dBallParticle::getShaderName()
{
	return "display3dballparticle_shader";
}

void Display3dBallParticle::setInfo( const ParticleItemVo info )
{
	Display3dParticle::setInfo(info);

	initBaseData();
	vector<GLfloat> basepos = initBasePos();
	initSpeed(basepos);

	BitmapDatas *bmp = new BitmapDatas(64,2,0xffff0000);
	bmp->setPixelByColorTransition(data.textureColor,0);
	bmp->setPixelByColorTransition(data.randomColor,1);

	getParticleData()->textureColor = Engine::getTextureManager()->getBitmapTexture(bmp,false);

}

void Display3dBallParticle::initBaseData()
{
	
	vector<GLfloat> verterAry;
	vector<GLfloat> uvAry;
	vector<GLushort> indexs;

	for(int i=0;i<data.totalNum;i++){
		makeRectangleData(verterAry,uvAry);
		indexs.push_back(0 + i * 4);
		indexs.push_back(1 + i * 4);
		indexs.push_back(2 + i * 4);
		indexs.push_back(0 + i * 4);
		indexs.push_back(2 + i * 4);
		indexs.push_back(3 + i * 4);
	}

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, verterAry.size() * sizeof(GLfloat), &verterAry[0], GL_STATIC_DRAW);
	objData->vertexBuffer = vertexBuffer;

	GLuint uvBuffer;
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvAry.size() * sizeof(GLfloat), &uvAry[0], GL_STATIC_DRAW);
	objData->uvBuffer = uvBuffer;

	GLuint indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexs.size() * sizeof(GLushort), &indexs[0], GL_STATIC_DRAW);
	objData->IndexBuffer = indexBuffer;
	objData->indexNum = indexs.size();

}

vector<GLfloat> Display3dBallParticle::initBasePos()
{
	vector<GLfloat> basePos;

	Vector3 v3d;
	Matrix ma;
	for(int i=0;i<data.totalNum;i++){
		v3d.set(0,0,0);
		if(data.isRandom){
			Vector3 roundv3d;
			roundv3d.set(data.round.X*data.round.W,data.round.Y*data.round.W,data.round.Z*data.round.W);

			if(data.closeSurface && (roundv3d.X == roundv3d.Y && roundv3d.Y == roundv3d.Z)){
				if(data.isEven){
					v3d.Z = roundv3d.Z;
					ma.identity();
					ma.appendRotationAxis(random() * 360,Vector3::X_AXIS);
					ma.appendRotationAxis(random() * 360,Vector3::Y_AXIS);
					v3d = ma.transformVector3(v3d);
				}else{
					v3d.Z = roundv3d.Z;
					ma.identity();
					ma.appendRotationAxis(random() * 360,Vector3::X_AXIS);
					ma.appendRotationAxis(random() * 360,Vector3::Y_AXIS);
					v3d = ma.transformVector3(v3d);
				}
			}else{
				v3d.set(roundv3d.X * random() * 2 - roundv3d.X,roundv3d.Y * random() * 2 - roundv3d.Y,roundv3d.Z * random() * 2 - roundv3d.Z);
			}

		}else{
			v3d.set(0,0,0);
		}

		v3d = v3d + data.basePositon;

		for(int j=0;j<4;j++){
			basePos.push_back(v3d.X);
			basePos.push_back(v3d.Y);
			basePos.push_back(v3d.Z);
			basePos.push_back(i * data.shootSpeed);
		}
	}

	GLuint basePosBuffer;
	glGenBuffers(1, &basePosBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, basePosBuffer);
	glBufferData(GL_ARRAY_BUFFER, basePos.size() * sizeof(GLfloat), &basePos[0], GL_STATIC_DRAW);
	getParticleData()->basePosBuffer = basePosBuffer;
	return basePos;
}

void Display3dBallParticle::makeRectangleData( vector<float> &verterList,vector<float> &uvList )
{
	float ranScale = random() * (data.particleRandomScale.X - data.particleRandomScale.Y) + data.particleRandomScale.Y;

	float offsetX = data.originWidthScale;
	float offsetY = data.originHeightScale;
	float width = data.width;
	float height = data.height;

	float verter[12]= {
		(-offsetX*width)*ranScale,(height-offsetY*height)*ranScale,0,
		(width-offsetX*width)*ranScale,(height-offsetY*height)*ranScale,0,
		(width-offsetX*width)*ranScale,(-offsetY*height)*ranScale,0,
		(-offsetX*width)*ranScale,(-offsetY*height)*ranScale,0};

	int isu = data.isU ? -1 : 1;
	int isv = data.isV ? -1 : 1;
	float ran = random();

	float uv[12] = {
		isu * 0.0f,				  isv * 0.0f,				ran,
		isu * 0.0f,				  isv * 1.0f/data.animRow,  ran,
		isu * 1.0f/data.animLine, isv * 1.0f/data.animRow,  ran,
		isu * 1.0f/data.animLine, isv * 0,					ran
	};

	if(data.isUV){
		float uv2[12] = {
			isu * 0.0f,				  isv * 1.0f/data.animRow, ran,
			isu * 1.0f/data.animLine, isv * 1.0f/data.animRow, ran,
			isu * 1.0f/data.animLine, isv * 0,				   ran,
			isu * 0.0f,				  isv * 0.0f,			   ran
		};
		for(unsigned int i=0;i<12;i++){
			uv[i] = uv2[i];
		}
	}

	for(int i=0;i<12;i++){
		verterList.push_back(verter[i]);
	}
	for(int i=0;i<12;i++){
		uvList.push_back(uv[i]);
	}

}

void Display3dBallParticle::setVa()
{
	glBindBuffer(GL_ARRAY_BUFFER,objData->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0,0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,objData->uvBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,0,0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER,getParticleData()->basePosBuffer);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE,0,0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER,getParticleData()->beMoveBuffer);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE,0,0);
	glEnableVertexAttribArray(3);
}

void Display3dBallParticle::setVc()
{
	glActiveTexture(GL_TEXTURE0);
	GLuint _programSlot = glGetUniformLocation(program, "tex0");
	glBindTexture(GL_TEXTURE_2D, objData->texture);
	glUniform1i(_programSlot, 0);

	glActiveTexture(GL_TEXTURE1);
	_programSlot = glGetUniformLocation(program, "tex1");
	glBindTexture(GL_TEXTURE_2D, getParticleData()->textureColor);
	glUniform1i(_programSlot, 1);

	GLuint _projectionSlot = glGetUniformLocation(program, "modelView");
	glUniformMatrix4fv(_projectionSlot,1,GL_FALSE,&(posMatrix->M[0][0]));

	

	_projectionSlot = glGetUniformLocation(program, "watheye");
	glUniformMatrix4fv(_projectionSlot,1,GL_FALSE,&(watchMatrix->M[0][0]));

	Matrix *camera = Engine::getCamera()->cameraMatrix;
	_projectionSlot = glGetUniformLocation(program, "camera");
	glUniformMatrix4fv(_projectionSlot,1,GL_FALSE,&(camera->M[0][0]));

	_programSlot = glGetUniformLocation(program, "time");
	glUniform4f(_programSlot,currentFrame,data.acceleration,data.life,data.isLoop? 1 : -1);

	_programSlot = glGetUniformLocation(program, "force");
	glUniform4f(_programSlot,data.addforce.X,data.addforce.Y,data.addforce.Z,0);

	_programSlot = glGetUniformLocation(program, "scale");
	glUniform4f(_programSlot,data.toscale,data.waveform.X,data.waveform.Y,1);

	_programSlot = glGetUniformLocation(program, "scaleCtrl");
	glUniform4f(_programSlot,data.widthFixed?0:1,data.heightFixed?0:1,data.paticleMaxScale-1,data.paticleMinScale-1);

	_programSlot = glGetUniformLocation(program, "animCtrl");
	glUniform4f(_programSlot,data.animLine,data.animRow,data.animInterval,1);

	_programSlot = glGetUniformLocation(program, "uvCtrl");
	glUniform4f(_programSlot,data.uSpeed,data.vSpeed,data.textureColor.hasData,data.randomColor.hasData);
}

ParticleBallData * Display3dBallParticle::getParticleData()
{
	return (ParticleBallData*)objData;
}

void Display3dBallParticle::initSpeed(const vector<GLfloat> &basePos)
{
	vector<float> beMove;

	Vector3 resultv3d;
	Vector3 v3d;

	for(int i=0;i<data.totalNum;i++){
		resultv3d.set(0,0,0);

		if(data.shootAngly.X != 0 || data.shootAngly.Y != 0 || data.shootAngly.Z != 0){//锥形速度
			float r = tan(data.shootAngly.W * PI /180 * random());
			float a = 360 * PI /180 * random();
			v3d.set(sin(a) * r,cos(a) * r,1);
			Matrix ma = getAxisMatrix(data.shootAngly);
			v3d = ma.transformVector3(v3d);
			v3d.normalize();
			resultv3d += v3d;
		}
		
		if(data.lixinForce.X != 0 || data.lixinForce.Y != 0 || data.lixinForce.Z != 0){
			v3d.set(random() > 0.5 ? -data.lixinForce.X:data.lixinForce.X,random() > 0.5 ? -data.lixinForce.Y:data.lixinForce.Y,random() > 0.5 ? -data.lixinForce.Z:data.lixinForce.Z);
			v3d.normalize();
			resultv3d += v3d;
		}
		
		if(data.islixinAngly){
			v3d.set(basePos[i*16],basePos[i*16 + 1],basePos[i*16 + 2]);
			v3d.normalize();
			resultv3d += v3d;
		}

		resultv3d.normalize();

		

		if(data.isSendRandom){
			resultv3d *= data.speed * random();
		}else{
			resultv3d *= data.speed;
		}

		float ranAngle = data.baseRandomAngle * random() * PI / 180;

		for(int j=0;j<4;j++){
			beMove.push_back(resultv3d.X);
			beMove.push_back(resultv3d.Y);
			beMove.push_back(resultv3d.Z);
			beMove.push_back(ranAngle);
		}
		
	}

	GLuint beMoveBuffer;
	glGenBuffers(1, &beMoveBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, beMoveBuffer);
	glBufferData(GL_ARRAY_BUFFER, beMove.size() * sizeof(GLfloat), &beMove[0], GL_STATIC_DRAW);
	getParticleData()->beMoveBuffer = beMoveBuffer;

}

Matrix Display3dBallParticle::getAxisMatrix( const Vector4 v3d )
{
	float xangle = atan(v3d.Y/v3d.Z) * 180 / PI;


	if(v3d.Y > 0 && v3d.Z < 0){
		xangle = 180 + xangle;
	}else if(v3d.Y < 0 && v3d.Z < 0){
		xangle = 180 + xangle;
	}

	

	float yangle = atan(v3d.X/v3d.Z) * 180 / PI;

	if(v3d.X > 0 && v3d.Z < 0){
		yangle = 180 + yangle;
	}else if(v3d.X < 0 && v3d.Z < 0){
		yangle = 180 + yangle;
	}

	if(v3d.Z == 0){
		if(v3d.Y > 0){
			xangle = 90;
		}else if(v3d.Y < 0){
			xangle = 270;
		}else{
			xangle = 0;
		}

		if(v3d.X > 0){
			yangle = 90;
		}else if(v3d.X < 0){
			yangle = 270;
		}else{
			yangle = 0;
		}
	}

	xangle = -xangle;
	yangle = yangle;

	Matrix ma;
	ma.appendRotationAxis(xangle,Vector3::X_AXIS);
	ma.appendRotationAxis(yangle,Vector3::Y_AXIS);
	return ma;
}

void Display3dBallParticle::updateTime( const int time )
{
	Display3dParticle::updateTime(time);
	watchMatrix->identity();
	watchEye(watchMatrix);
	Display3dParticle::updatePosMatrix();

	currentFrame = _time/FRAMETIME;
	currentFrame *= data.playSpeed;

}

void Display3dBallParticle::watchEye( Matrix *ma )
{
	if(data.watchEye){

		ma->prependMultiply(inverseBindMatrix);

		ma->prependRotationAxis(-45 , Vector3::Y_AXIS);
		ma->prependRotationAxis(30, Vector3::X_AXIS);
	}

	if(data.ziZhuanAngly.W != 0){  //显示自转
		ma->prependRotationAxis(_time*data.ziZhuanAngly.W,Vector3(data.ziZhuanAngly.X,data.ziZhuanAngly.Y,data.ziZhuanAngly.Z));
	}
}



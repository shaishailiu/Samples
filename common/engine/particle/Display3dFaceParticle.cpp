#include "vo/ObjData.h"
#include "utils/BindAttrib.h"
#include "Engine.h"
#include "EngineConfig.h"
#include "layer/LayerManager.h"
#include "utils/Camera3D.h"
#include "math/Matrix.h"
#include "Display3dFaceParticle.h"
#include "log/LogTrace.h"


Display3dFaceParticle::Display3dFaceParticle(void)
	: currentUV(),currentColorIndex(0)
{
	//objData = nullptr;

	objData = new ObjData();
}


Display3dFaceParticle::~Display3dFaceParticle(void)
{
	if(objData != nullptr){
		delete objData;
	}
}


void Display3dFaceParticle::setInfo( const ParticleItemVo info )
{
	Display3dParticle::setInfo(info);
	initParticleData();
}

void Display3dFaceParticle::initParticleData()
{
	float offsetX = data.originWidthScale;
	float offsetY = data.originHeightScale;
	float width = data.width;
	float height = data.height;

	float verter[12]= {
		-offsetX*width,height-offsetY*height,0,
		width-offsetX*width,height-offsetY*height,0,
		width-offsetX*width,-offsetY*height,0,
		-offsetX*width,-offsetY*height,0};
	
	int isu = data.isU ? -1 : 1;
	int isv = data.isV ? -1 : 1;

	float uv[8] = {
			isu * 0.0f,				  isv * 0.0f,
			isu * 0.0f,				  isv * 1.0f/data.animRow,
			isu * 1.0f/data.animLine, isv * 1.0f/data.animRow,
			isu * 1.0f/data.animLine, isv * 0
		}; 
	
	if(data.isUV){
		float uv2[8] = {
			isu * 0.0f,				  isv * 1.0f/data.animRow,
			isu * 1.0f/data.animLine, isv * 1.0f/data.animRow,
			isu * 1.0f/data.animLine, isv * 0,
			isu * 0.0f,				  isv * 0.0f
		};
		for(unsigned int i=0;i<8;i++){
			uv[i] = uv2[i];
		}
	}

	unsigned short indexs[6] = {0, 1, 2, 0, 2, 3};
	

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), verter, GL_STATIC_DRAW);
	objData->vertexBuffer = vertexBuffer;

	GLuint uvBuffer;
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), uv, GL_STATIC_DRAW);
	objData->uvBuffer = uvBuffer;

	GLuint indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLushort), indexs, GL_STATIC_DRAW);
	objData->IndexBuffer = indexBuffer;
	objData->indexNum = 6;

	
}

vector<BindAttrib> Display3dFaceParticle::getBindAtt()
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

	return vec;
}

std::string Display3dFaceParticle::getShaderName()
{
	return "display3dfaceparticle_shader";
}

void Display3dFaceParticle::setVa()
{
	glBindBuffer(GL_ARRAY_BUFFER,objData->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0,0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,objData->uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,0,0);
	glEnableVertexAttribArray(1);
}

void Display3dFaceParticle::setVc()
{
	GLuint _textureSlot = glGetUniformLocation(program, "tex0");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, objData->texture);
	glUniform1i(_textureSlot, 0);

	_textureSlot = glGetUniformLocation(program, "uv");
	glUniform2f(_textureSlot,currentUV[0],currentUV[1]);

	_textureSlot = glGetUniformLocation(program, "color");
	glUniform4f(_textureSlot,data.textureColor.data[currentColorIndex].X,data.textureColor.data[currentColorIndex].Y,
		data.textureColor.data[currentColorIndex].Z,data.textureColor.data[currentColorIndex].W);

	GLuint _projectionSlot = glGetUniformLocation(program, "modelView");
	glUniformMatrix4fv(_projectionSlot,1,GL_FALSE,&(posMatrix->M[0][0]));

	Matrix *camera = Engine::getCamera()->cameraMatrix;
	_projectionSlot = glGetUniformLocation(program, "camera");
	glUniformMatrix4fv(_projectionSlot,1,GL_FALSE,&(camera->M[0][0]));
}

void Display3dFaceParticle::updateUV()
{
	int currentFrame = _time/FRAMETIME;
	currentFrame = currentFrame > data.maxAnimTime ? data.maxAnimTime : currentFrame;
	currentFrame = (currentFrame/data.animInterval)%(data.animLine*data.animRow);

	int cf = _time/FRAMETIME;

	currentUV[0] = int(currentFrame%data.animLine)/(float)data.animLine + cf * data.uSpeed;
	currentUV[1] = int(currentFrame/data.animLine)/(float)data.animRow + cf * data.vSpeed;
}

void Display3dFaceParticle::updateTime( const int time )
{
	Display3dParticle::updateTime(time);
	Display3dParticle::watchEye(posMatrix);
	Display3dParticle::updatePosMatrix();

	updateUV();
	updateColor();

	int currentFrame = _time/FRAMETIME;

	if(currentFrame > (data.life-2)){
		visible = false;
	}

}

void Display3dFaceParticle::updateColor()
{
	int cf = _time/FRAMETIME;
	float currentColorPer = (cf%data.life)/(float)data.life;
	currentColorIndex = currentColorPer * 64;
	//trace(currentColorIndex);
	/*
	var per:Number = Math.abs((_timer/Scene_data.frameTime/_life)%1);
	var color:Vector3D = _textureColorAry[int((_textureColorAry.length-1)*per)]

	if(_colorChange){
		_colorVec[0] = 1+_colorChange.rValue*_colorChange.num;
		_colorVec[1] = 1+_colorChange.gValue*_colorChange.num;
		_colorVec[2] = 1+_colorChange.bValue*_colorChange.num;
		_colorVec[3] = (1+_colorChange.aValue*_colorChange.num) * _alpha;
	}else{
		_colorVec[3] = _alpha;
	}

	return Vector.<Number>([_colorVec[0] * color.x,_colorVec[1] * color.y,_colorVec[2] * color.z,_colorVec[3] * color.w]);
	*/
}
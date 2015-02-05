#include "ParticleItemVo.h"
#include "Engine.h"
#include "EngineConfig.h"
#include "texture/TextureManager.h"
#include "vo/ObjData.h"
#include "utils/Camera3D.h"
#include "layer/LayerManager.h"
#include "utils/BitmapDatas.h"
#include "Display3dParticle.h"



Display3dParticle::Display3dParticle(void)
{
	bindTarget = nullptr;
}


Display3dParticle::~Display3dParticle(void)
{
}

void Display3dParticle::setInfo( const ParticleItemVo info )
{
	//pdata = info;
	data = info.display;
	timeline.setData(info.timeline);
	_beginTime = timeline.beginTime;

	objData->texture = Engine::getTextureManager()->getPngTexture(PERROOT + string("particle/") + data.textureUrl,true);
	//BitmapDatas *bmp = new BitmapDatas(64,4,0xffff0000);
	//bmp->setPixelByColorTransition(data.textureColor,0);
	//objData->texture = Engine::getTextureManager()->getBitmapTexture(bmp,false);
}

void Display3dParticle::setVa()
{

}

void Display3dParticle::setVc()
{

}

void Display3dParticle::updatePosMatrix()
{
	
	//posMatrix->appendRotationAxis(90,Vector3::Y_AXIS);

	posMatrix->appendScale(Vector3(0.1,0.1,0.1));

	if(bindTarget){
		
		//posMatrix->appendRotationAxis(bindTarget->getRotationY(),Vector3::Y_AXIS);
		
		bindMatrix.identity();
		bindMatrix.prependRotationAxis(bindTarget->getRotationY(),Vector3::Y_AXIS);

		bindMatrix.getInverse(inverseBindMatrix);

		posMatrix->multiply(bindMatrix);

		_x = bindTarget->getX();
		_y = bindTarget->getZ();

		Vector3 pos = Engine::getCamera()->math2dto3d(_x + Engine::getScene()->getX(),_y + Engine::getScene()->getY()); 
		posMatrix->appendTranslation(pos);
	}

}

void Display3dParticle::watchEye(Matrix *ma)
{
	if(data.watchEye){

		ma->prependMultiply(inverseBindMatrix);

		ma->prependRotationAxis(-45 , Vector3::Y_AXIS);
		ma->prependRotationAxis(30, Vector3::X_AXIS);
	}
}

void Display3dParticle::updateTime( const int time )
{
	_time = time - _beginTime;

	timeline.updateTime(time);

	visible = timeline.visible;

	posMatrix->identity();
	
	timeline.updateMatrix(posMatrix,data);

	//updatePosMatrix();

}

void Display3dParticle::update()
{
	if(!visible){ 
		return;
	}
	setBlendFactors(data.alphaMode);
	Display3D::update();
}

void Display3dParticle::setBlendFactors( const int &type )
{
	switch(type){
	case 0:
		glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);  
		//_context3D.setBlendFactors(Context3DBlendFactor.ONE,Context3DBlendFactor.ONE_MINUS_SOURCE_ALPHA);
		break;
	case 1:
		glBlendFunc(GL_ONE,GL_ONE);
		//_context3D.setBlendFactors(Context3DBlendFactor.ONE,Context3DBlendFactor.ONE);
		break;
	case 2:    
		glBlendFunc(GL_DST_COLOR,GL_ZERO);
		//_context3D.setBlendFactors(Context3DBlendFactor.DESTINATION_COLOR,Context3DBlendFactor.ZERO);
		break;
	case 3:
		glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_COLOR);
		//_context3D.setBlendFactors(Context3DBlendFactor.ONE,Context3DBlendFactor.ONE_MINUS_SOURCE_COLOR);
		break;
	case 4:
		glBlendFunc(GL_SRC_ALPHA ,GL_ONE);
		//_context3D.setBlendFactors(Context3DBlendFactor.SOURCE_ALPHA,Context3DBlendFactor.ONE);
		break;
	}
}

void Display3dParticle::reset()
{
	timeline.reset();
	updateTime(0);
}

int Display3dParticle::getMaxFrame()
{
	return timeline.maxFrameNum;
}



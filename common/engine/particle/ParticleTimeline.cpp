#include "Engine.h"
#include "EngineConfig.h"
#include "ParticleTimeline.h"
#include "log/LogTrace.h"

FrameTimeUtils ParticleTimeline::frameutils;

ParticleTimeline::ParticleTimeline(void)
{
	targetFlag = -1;
	visible = false;
	maxFrameNum = 0;
	_time = 0;

	_selfRotaion = nullptr;
	_axisRotaion = nullptr;
	_centrifugal = nullptr;
	_axisMove    = nullptr;
	_colorChange = nullptr;
	_scaleChange = nullptr;
	_scaleAnim   = nullptr;
	_scaleNosie  = nullptr;

}


ParticleTimeline::~ParticleTimeline(void)
{
	if(_selfRotaion){
		delete _selfRotaion;
	}
	if(_axisRotaion){
		delete _axisRotaion;
	}
	if(_centrifugal){
		delete _centrifugal;
	}
	if(_axisMove){
		delete _axisMove;
	}
	if(_colorChange){
		delete _colorChange;
	}
	if(_selfRotaion){
		delete _selfRotaion;
	}
	if(_scaleChange){
		delete _scaleChange;
	}
	if(_scaleAnim){
		delete _scaleAnim;
	}

	if(_scaleNosie){
		delete _scaleNosie;
	}
}

void ParticleTimeline::updateTime(const int time)
{
	if(_currentKeyFrame == nullptr){
		return;
	}
	_time = time;
	//_time ++;
	//trace(_time);

	getTarget();

	if(_axisRotaion)
		_axisRotaion->update(time);

	if(_selfRotaion){
		_selfRotaion->update(time);
	}

	if(_axisMove)
		_axisMove->update(time);
	if(_scaleChange){
		_scaleChange->update(time);
	}else if(_scaleNosie){
		_scaleNosie->update(time);
	}else if(_scaleAnim){
		_scaleAnim->update(time);
	}
}

void ParticleTimeline::setData( const std::vector<ParticleAnimVo> ary )
{
	_keyFrameAry = ary;

	_currentKeyFrame = &(_keyFrameAry[0]);

	//frameutils.process(_keyFrameAry);

	maxFrameNum = ary[ary.size()-1].frameNum;

	beginTime = ary[0].frameNum * FRAMETIME;

	ParticleTimeline::frameutils.process(_keyFrameAry);

}

void ParticleTimeline::getTarget()
{
	int flag = -1;
	for(int i=0;i<_keyFrameAry.size();i++){
		if(_keyFrameAry[i].frameNum * Engine::getConfig()->frameTime < _time){
			flag = i;
		}else{
			break;
		}
	}
	if(flag != targetFlag){
		_currentKeyFrame = &(_keyFrameAry[flag]);
		targetFlag = flag;

		if(flag == (_keyFrameAry.size()-1)){
			visible = false;
			_currentKeyFrame = nullptr;
		}else{
			visible = true;
			float baset = _currentKeyFrame->frameNum * FRAMETIME;
			enterKeyFrame(_currentKeyFrame->animframevec,baset,_currentKeyFrame->baseValue);
		}
	}
}

void ParticleTimeline::enterKeyFrame( const std::vector<ParticleAnimFrameVo> ary,const float baseTime ,const float baseValueAry[])
{
	for(unsigned int i=0;i<10;i++){

		if(!baseValueAry[i]){
			continue;
		}

		switch(ary[i].type){
		case 1:
			if(!_selfRotaion)
				_selfRotaion = new SelfRotation;
			_selfRotaion->num = _selfRotaion->baseNum = baseValueAry[i];
			break;
		case 2:
			if(!_axisRotaion)
				_axisRotaion = new AxisRotaion;
			_axisRotaion->num =_axisRotaion->baseNum = baseValueAry[i];
			break;
		case 3:
			//if(!_centrifugal)
			//	_centrifugal = new Centrifugal;
			//_centrifugal->num = _centrifugal->baseNum = baseValueAry[i];
			break;
		case 4:
			if(!_colorChange)
				_colorChange = new ColorChange;
			_colorChange->num = _colorChange->baseNum = baseValueAry[i];
			break;
		case 6:
			if(!_scaleChange)
				_scaleChange = new ScaleChange;
			_scaleChange->num = _scaleChange->baseNum = baseValueAry[i];
			break;
		case 7:
			if(!_scaleAnim)
				_scaleAnim = new ScaleAnim;
			_scaleAnim->num = _scaleAnim->baseNum = baseValueAry[i];
			break;
		case 8:
			if(!_scaleNosie)
				_scaleNosie = new ScaleNoise;
			_scaleNosie->num = _scaleNosie->baseNum = baseValueAry[i];
			break;
		case 9:
			if(!_axisMove)
				_axisMove = new AxisMove;
			_axisMove->num = _axisMove->baseNum = baseValueAry[i];
			break;
		}

	}

	if(_selfRotaion)
		_selfRotaion->isDeath = true;
	if(_axisRotaion)
		_axisRotaion->isDeath = true;
	//if(_centrifugal)
	//	_centrifugal->isDeath = true;
	if(_colorChange)
		_colorChange->isDeath = true;
	if(_scaleChange)
		_scaleChange->isDeath = true;
	if(_scaleAnim)
		_scaleAnim->isDeath = true;
	if(_scaleNosie)
		_scaleNosie->isDeath = true;
	if(_axisMove)
		_axisMove->isDeath = true;

	for(unsigned int i=0;i<ary.size();i++){
		if(ary[i].type == 1){
			if(!_selfRotaion){
				_selfRotaion = new SelfRotation;
			}else{
				_selfRotaion->reset();
			}
			_selfRotaion->setData(ary[i].dataVec);
			_selfRotaion->baseTime = baseTime;
		}else if(ary[i].type == 2){
			if(!_axisRotaion){
				_axisRotaion = new AxisRotaion;
			}else{
				_axisRotaion->reset();
			}
			_axisRotaion->setData(ary[i].dataVec);
			_axisRotaion->baseTime = baseTime;
		}else if(ary[i].type == 3){
			/*
			if(!_centrifugal){
				_centrifugal = new Centrifugal;
			}else{
				_centrifugal->reset();
			}
			_centrifugal->setData(ary[i].dataVec);
			_centrifugal->baseTime = baseTime;
			*/
		}else if(ary[i].type == 4){
			if(!_colorChange){
				_colorChange = new ColorChange;
			}else{
				_colorChange->reset();
			}
			_colorChange->setData(ary[i].dataVec);
			_colorChange->baseTime = baseTime;
		}else if(ary[i].type == 6){
			if(!_scaleChange){
				_scaleChange = new ScaleChange;
			}else{
				_scaleChange->reset();
			}
			_scaleChange->setData(ary[i].dataVec);
			_scaleChange->baseTime = baseTime;
		}else if(ary[i].type == 7){
			if(!_scaleAnim){
				_scaleAnim = new ScaleAnim;
			}else{
				_scaleAnim->reset();
			}
			_scaleAnim->setData(ary[i].dataVec);
			_scaleAnim->baseTime = baseTime;
		}else if(ary[i].type == 8){
			if(!_scaleNosie){
				_scaleNosie = new ScaleNoise;
			}else{
				_scaleNosie->reset();
			}
			_scaleNosie->setData(ary[i].dataVec);
			_scaleNosie->baseTime = baseTime;
		}else if(ary[i].type == 9){
			if(!_axisMove){
				_axisMove = new AxisMove;
			}else{
				_axisMove->reset();
			}
			_axisMove->setData(ary[i].dataVec);
			_axisMove->baseTime = baseTime;
		}
	}

}

void ParticleTimeline::updateMatrix( Matrix *posMatrix ,const ParticleDisplayVo &data)
{

	if(_axisMove){
		posMatrix->prependTranslation(_axisMove->axis.X*_axisMove->num, _axisMove->axis.Y*_axisMove->num, _axisMove->axis.Z*_axisMove->num);
	}

	if(_axisRotaion){
		//posMatrix->prependTranslation(_axisRotaion->axisPos);
		posMatrix->prependRotationAxis(_axisRotaion->num,_axisRotaion->axis);
		//posMatrix->prependTranslation(-_axisRotaion->axisPos);
	}

	posMatrix->prependTranslation(data.center.X, data.center.Y, data.center.Z);

	if(_scaleChange){
		//processScale();
		posMatrix->prependScale(data.widthFixed?1:1,data.heightFixed?1:_scaleChange->num,_scaleChange->num);
	}else if(_scaleNosie){
		//processNosie();
		posMatrix->prependScale(data.widthFixed?1:(1+_scaleNosie->num),data.heightFixed?1:(1+_scaleNosie->num),1+_scaleNosie->num);
	}else if(_scaleAnim){
		//processScaleAnim();
		posMatrix->prependScale(data.widthFixed?1:_scaleAnim->num,data.heightFixed?1:_scaleAnim->num,_scaleAnim->num);
	}

	posMatrix->prependRotationAxis(data.rotationX,Vector3::X_AXIS);
	posMatrix->prependRotationAxis(data.rotationY,Vector3::Y_AXIS);
	posMatrix->prependRotationAxis(data.rotationZ,Vector3::Z_AXIS);

	if(data.ziZhuanAngly.X != 0 || data.ziZhuanAngly.Y != 0 || data.ziZhuanAngly.Z != 0){
		if(_selfRotaion){
			posMatrix->prependRotationAxis(_selfRotaion->num,Vector3(data.ziZhuanAngly.X,data.ziZhuanAngly.Y,data.ziZhuanAngly.Z));
		}
	}


	/*
	posMatrix.identity();
	posMatrix.prependScale(overAllScale*outScale,overAllScale*outScale,overAllScale*outScale);
	posMatrix.prependScale(Scene_data.mainScale/2,Scene_data.mainScale/2,Scene_data.mainScale/2);
	if(_axisMove)
		posMatrix.prependTranslation(_axisMove.axis.x*_axisMove.num, _axisMove.axis.y*_axisMove.num, _axisMove.axis.z*_axisMove.num);

	if(_axisRotaion){
		posMatrix.prependRotation(_axisRotaion.num,_axisRotaion.axis,_axisRotaion.axisPos);
	}

	if(_centrifugal){
		_basePos = new Vector3D(this._absoluteX, this._absoluteY, this._absoluteZ);
		var tempVec:Vector3D = _basePos.subtract(_centrifugal.center)
			tempVec.scaleBy(1+_centrifugal.num);
		tempVec = tempVec.add(_centrifugal.center);
		posMatrix.prependTranslation(tempVec.x,tempVec.y,tempVec.z);
	}else{
		posMatrix.prependTranslation(this._absoluteX, this._absoluteY, this._absoluteZ);
	}

	if(_scaleChange){ 
		processScale();
	}else if(_scaleNosie){
		processNosie();
	}else if(_scaleAnim){
		processScaleAnim();
	}else{
		posMatrix.prependScale(this._scale,this._scale,this._scale);
	}


	posMatrix.prependRotation(_rotationX , Vector3D.X_AXIS);
	posMatrix.prependRotation(_rotationY , Vector3D.Y_AXIS);
	posMatrix.prependRotation(_rotationZ , Vector3D.Z_AXIS);
	*/
}

float ParticleTimeline::getSelfNum()
{
	if(_selfRotaion){
		return _selfRotaion->num;
	}else{
		return 0;
	}
}

void ParticleTimeline::reset()
{
	targetFlag = -1;
	visible = false;
	_currentKeyFrame = &(_keyFrameAry[0]);


	if(_selfRotaion){
		_selfRotaion->depthReset();
	}
	if(_axisRotaion){
		_axisRotaion->depthReset();
	}
	if(_centrifugal){
		_centrifugal->depthReset();
	}
	if(_axisMove){
		_axisMove->depthReset();
	}
	if(_colorChange){
		_colorChange->depthReset();
	}
	if(_selfRotaion){
		_selfRotaion->depthReset();
	}
	if(_scaleChange){
		_scaleChange->depthReset();
	}
	if(_scaleAnim){
		_scaleAnim->depthReset();
	}

	if(_scaleNosie){
		_scaleNosie->depthReset();
	}

}

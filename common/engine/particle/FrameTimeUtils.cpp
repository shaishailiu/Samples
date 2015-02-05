#include "EngineConfig.h"
#include "FrameTimeUtils.h"


FrameTimeUtils::FrameTimeUtils(void)
{
}


FrameTimeUtils::~FrameTimeUtils(void)
{
}

void FrameTimeUtils::process( std::vector<ParticleAnimVo> &timeline )
{
	reset();

	for(unsigned int i=1;i<timeline.size()-1;i++){
		float baseTime = timeline[i-1].frameNum * FRAMETIME;
		float lastTime = (timeline[i].frameNum - timeline[i-1].frameNum) * FRAMETIME;
		
		std::vector<ParticleAnimFrameVo> *animData = &(timeline[i].animframevec);
		
		
		for(unsigned int j=1;j<animData->size();j++){

			if((*animData)[j].type == 1){
				_selfRotaion.setData((*animData)[j].dataVec);
				_selfRotaion.getAllNum(lastTime);
			}else if((*animData)[j].type == 2){
				_axisRotaion.setData((*animData)[j].dataVec);
				_axisRotaion.getAllNum(lastTime);
			}else if((*animData)[j].type == 3){
				_centrifugal.setData((*animData)[j].dataVec);
				_centrifugal.getAllNum(lastTime);
			}else if((*animData)[j].type == 4){
				_colorChange.setData((*animData)[j].dataVec);
				_colorChange.getAllNum(lastTime);
			}else if((*animData)[j].type == 6){
				_scaleChange.setData((*animData)[j].dataVec);
				_scaleChange.getAllNum(lastTime);
			}else if((*animData)[j].type == 7){
				_scaleAnim.setData((*animData)[j].dataVec);
				_scaleAnim.getAllNum(lastTime);
			}else if((*animData)[j].type == 8){
				_scaleNosie.setData((*animData)[j].dataVec);
				_scaleNosie.getAllNum(lastTime);
			}else if((*animData)[j].type == 9){
				_axisMove.setData((*animData)[j].dataVec);
				_axisMove.getAllNum(lastTime);
			}

		}

		timeline[i].baseValue[1] = _selfRotaion.baseNum;
		timeline[i].baseValue[2] = _axisRotaion.baseNum;
		timeline[i].baseValue[3] = _centrifugal.baseNum;
		timeline[i].baseValue[4] = _colorChange.baseNum;
		timeline[i].baseValue[6] = _scaleChange.baseNum;
		timeline[i].baseValue[7] = _scaleAnim.baseNum;
		timeline[i].baseValue[8] = _scaleNosie.baseNum;
		timeline[i].baseValue[9] = _axisMove.baseNum;
		
	}
}

void FrameTimeUtils::reset()
{
	_selfRotaion.depthReset();
	_axisRotaion.depthReset();
	_centrifugal.depthReset();
	_axisMove.depthReset();
	_colorChange.depthReset();
	_scaleChange.depthReset();
	_scaleAnim.depthReset();
	_scaleNosie.depthReset();
}

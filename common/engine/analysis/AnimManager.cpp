#include "log/LogTrace.h"
#include "vo/MeshVo.h"
#include "math/Vector.h"
#include "vo/AnimData.h"
#include "utils/FileUtils.h"
#include "utils/Memory.h"
#include "AnimManager.h"


AnimManager::AnimManager(void)
{
	animDic = new map<string,AnimData*>;
}


AnimManager::~AnimManager(void)
{

}

AnimData *AnimManager::getAnim( string fileUrl )
{
	if(hasCache(fileUrl)){
		return (*animDic)[fileUrl];
	}

	Memory *memory = FileUtils::loadFile(fileUrl.c_str());

	if(memory == NULL){
		return NULL;
	}

	/*读取循环帧*/	
	int inLoop;
	//fread(&inLoop,sizeof(int),1,fp);
	memory->read(&inLoop,sizeof(int));

	/* 读取插值数组 */	
	vector<int> interAry;
	int interLenght;
	//fread(&interLenght,sizeof(int),1,fp);
	memory->read(&interLenght,sizeof(int));

	for(int i=0;i<interLenght;i++){
		int num;
		//fread(&num,sizeof(int),1,fp);
		memory->read(&num,sizeof(int));
		interAry.push_back(num);
	}

	/*读取包围盒*/
	vector<Vector3> boundsAry;
	int boundLength;
	//fread(&boundLength,sizeof(int),1,fp);
	memory->read(&boundLength,sizeof(int));
	for(int i=0;i<boundLength;i++){
		Vector3 vec3;
		//fread(&(vec3.X),sizeof(float),1,fp);
		//fread(&(vec3.Y),sizeof(float),1,fp);
		//fread(&(vec3.Z),sizeof(float),1,fp);

		memory->read(&(vec3.X),sizeof(float));
		memory->read(&(vec3.Y),sizeof(float));
		memory->read(&(vec3.Z),sizeof(float));

		boundsAry.push_back(vec3);
	}

	/*写入名字高度	*/
	int nameHeight;
	//fread(&nameHeight,sizeof(int),1,fp);
	memory->read(&nameHeight,sizeof(int));
		
	/*写入基础骨骼信息*/	
	vector<ObjectBone> hierarchyList;
	int hierarchyLength;
	//fread(&hierarchyLength,sizeof(int),1,fp);
	memory->read(&hierarchyLength,sizeof(int));

	for(int i=0;i<hierarchyLength;i++){
		ObjectBone objBone;
		//fread(&(objBone.father),sizeof(int),1,fp);
		//fread(&(objBone.changtype),sizeof(int),1,fp);
		//fread(&(objBone.startIndex),sizeof(int),1,fp);

		memory->read(&(objBone.father),sizeof(int));
		memory->read(&(objBone.changtype),sizeof(int));
		memory->read(&(objBone.startIndex),sizeof(int));

		//fread(&(objBone.tx),sizeof(float),1,fp);
		//fread(&(objBone.ty),sizeof(float),1,fp);
		//fread(&(objBone.tz),sizeof(float),1,fp);

		//fread(&(objBone.qx),sizeof(float),1,fp);
		//fread(&(objBone.qy),sizeof(float),1,fp);
		//fread(&(objBone.qz),sizeof(float),1,fp);

		memory->read(&(objBone.tx),sizeof(float));
		memory->read(&(objBone.ty),sizeof(float));
		memory->read(&(objBone.tz),sizeof(float));

		memory->read(&(objBone.qx),sizeof(float));
		memory->read(&(objBone.qy),sizeof(float));
		memory->read(&(objBone.qz),sizeof(float));

		hierarchyList.push_back(objBone);
	}
	
	/*写入帧数 */		
	vector< vector<float> > frameAry;
	int frameAryLength;
	//fread(&frameAryLength,sizeof(int),1,fp);
	memory->read(&frameAryLength,sizeof(int));

	for(int i=0;i<frameAryLength;i++){
		vector<float> frameItemAry;

		int frameItemAryLength;
		//fread(&frameItemAryLength,sizeof(int),1,fp);
		memory->read(&frameItemAryLength,sizeof(int));

		for(int j=0;j<frameItemAryLength;j++){
			float frameNum;
			//fread(&frameNum,sizeof(float),1,fp);
			memory->read(&frameNum,sizeof(float));
			frameItemAry.push_back(frameNum);
		}

		frameAry.push_back(frameItemAry);
			
	}

	vector< vector<ObjectBone> > newFrameAry;
	for(int i=0;i<frameAry.size();i++){
		newFrameAry.push_back(frameToBone(frameAry[i],hierarchyList));
	}

	setFrameToMatrix(newFrameAry);

	AnimData *anim = new AnimData;

	anim->setData(newFrameAry);

	animDic->insert(make_pair(fileUrl,anim));

	delete memory;

	return anim;
}

vector<ObjectBone> AnimManager::frameToBone( vector<float> &frameData,vector<ObjectBone> &hierarchyList )
{
	vector<ObjectBone> _arr;
	
	for(int i=0;i<hierarchyList.size();i++){
		ObjectBone _temp;
		_temp.father = hierarchyList[i].father;
		_temp.tx=hierarchyList[i].tx;
		_temp.ty=hierarchyList[i].ty;
		_temp.tz=hierarchyList[i].tz;
		_temp.qx=hierarchyList[i].qx;
		_temp.qy=hierarchyList[i].qy;
		_temp.qz=hierarchyList[i].qz;

		int k = 0;
		if (hierarchyList[i].changtype & 1){
			_temp.tx = frameData[hierarchyList[i].startIndex + k];
			++k;
		}
		if (hierarchyList[i].changtype & 2){
			_temp.ty = frameData[hierarchyList[i].startIndex + k];
			++k;
		}
		if (hierarchyList[i].changtype & 4){
			_temp.tz = frameData[hierarchyList[i].startIndex + k];
			++k;
		}
		if (hierarchyList[i].changtype & 8){
			_temp.qx = frameData[hierarchyList[i].startIndex + k];
			++k;
		}
		if (hierarchyList[i].changtype & 16){
			_temp.qy = frameData[hierarchyList[i].startIndex + k];
			++k;
		}
		if (hierarchyList[i].changtype & 32){
			_temp.qz = frameData[hierarchyList[i].startIndex + k];
			++k;
		}
		_arr.push_back(_temp);
	}
	
	return _arr;
}

void AnimManager::setFrameToMatrix(vector< vector<ObjectBone> > &frameAry){
	//return;
	for(int j=0;j<frameAry.size();j++){
		vector<ObjectBone> *boneAry;
		boneAry = &frameAry[j];

		Quaternion Q0;
		Quaternion Q1;
		Quaternion OldQ;
		Matrix OldM;
		Matrix newM;
		Matrix tempM;
		//Matrix tempObj:ObjectBone=new ObjectBone;

		for(int i=0;i<boneAry->size();i++){

			//var _M1:Matrix3D=new Matrix3D;

			ObjectBone *xyzfarme0;
			xyzfarme0 = &(*boneAry)[i];
			Q0.setXYZ(xyzfarme0->qx,xyzfarme0->qy,xyzfarme0->qz);
			//ObjectBone sonBone = xyzfarme0;

			ObjectBone *fatherBone;

			if(xyzfarme0->father==-1){
				OldQ.setXYZ(xyzfarme0->qx,xyzfarme0->qy,xyzfarme0->qz);
				//newM=OldQ.toMatrix3D();
				newM.identity();
				newM.setRotation(OldQ);
				//newM.appendTranslation(xyzfarme0->tx,xyzfarme0->ty,xyzfarme0->tz);
				newM.setTranslation(Vector3(xyzfarme0->tx,xyzfarme0->ty,xyzfarme0->tz));
				//newM.appendRotation(-90,Vector3D.X_AXIS);
				Quaternion q;
				q.setEuler_yxz(Vector3(0,-90*PI/180,0));
				tempM.identity();
				tempM.setRotation(q);
				newM = newM * tempM;
				Quaternion fatherQ = newM.getRotation();
				
				Vector3 position = newM.getTranslation();

				xyzfarme0->tx=position.X;
				xyzfarme0->ty=position.Y;
				xyzfarme0->tz=position.Z;
				//xyzfarme0->tw=newM.position.w;

				xyzfarme0->qx=fatherQ.X;
				xyzfarme0->qy=fatherQ.Y;
				xyzfarme0->qz=fatherQ.Z;
				xyzfarme0->qw=fatherQ.W;

				//newM.appendScale(-1,1,1);
				tempM.identity();
				tempM.setTransform(Vector3(0,0,0),Quaternion(0,0,0,0),Vector3(-1,1,1));

				newM = newM * tempM;

				//newM.setTransform(Vector3(0,0,0),Quaternion(),Vector3(-1,1,1));

				xyzfarme0->matrix = newM;

			}else {
				fatherBone = &(*boneAry)[xyzfarme0->father];
				OldQ.identify();
				OldQ.set(fatherBone->qx,fatherBone->qy,fatherBone->qz,fatherBone->qw);


				OldM.identity();
				OldM.setRotation(OldQ);
				OldM.setTranslation(Vector3(fatherBone->tx,fatherBone->ty,fatherBone->tz));

				Vector3 tempV = OldM.transformVector3(Vector3(xyzfarme0->tx,xyzfarme0->ty,xyzfarme0->tz));
				
				//Q1.multiply(OldQ,Q0);
				Q1 = Q0 * OldQ;
				newM.identity();
				newM.setRotation(Q1);
				//newM.appendTranslation(tempV.x,tempV.y,tempV.z);
				newM.setTranslation(Vector3(tempV.X,tempV.Y,tempV.Z));
				//tempM=newM;

				xyzfarme0->qx=Q1.X;
				xyzfarme0->qy=Q1.Y;
				xyzfarme0->qz=Q1.Z;
				xyzfarme0->qw=Q1.W;

				xyzfarme0->tx=tempV.X;
				xyzfarme0->ty=tempV.Y;
				xyzfarme0->tz=tempV.Z;
				//xyzfarme0->tw=tempV.w;

				//tempM.appendScale(-1,1,1);
				//newM.setTransform(Vector3(0,0,0),Quaternion(),Vector3(-1,1,1));
				tempM.identity();
				tempM.setTransform(Vector3(0,0,0),Quaternion(0,0,0,0),Vector3(-1,1,1));

				newM = newM * tempM;

				xyzfarme0->matrix = newM;

			}
			//context.setProgramConstantsFromMatrix(Context3DProgramType.VERTEX, 12+i*4,  tempM, true);
		}
	}
}

bool AnimManager::hasCache( string &fileUrl )
{
	map<string,AnimData*>::iterator it;
	it = animDic->find(fileUrl);

	if(it == animDic->end()){
		return false;
	}else {
		return true;
	}
}

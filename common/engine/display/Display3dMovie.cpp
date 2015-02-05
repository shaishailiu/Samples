#include "Engine.h"
#include "log/LogTrace.h"
#include "layer/LayerManager.h"
#include "analysis/MeshManager.h"
#include "analysis/AnimManager.h"
#include "texture/TextureManager.h"
#include "utils/BindAttrib.h"
#include "vo/MeshData.h"
#include "vo/AnimData.h"
#include "utils/Camera3D.h"
#include "utils/StringUtils.h"
#include <functional>

#include "Display3dMovie.h"


Display3dMovie::Display3dMovie(void)
{
	initData();
	_time = 0;
	speedX = 0;
	speedZ = 0;
	_completeState = 0;
	isLock = false;
}


Display3dMovie::~Display3dMovie(void)
{
}

vector<BindAttrib> Display3dMovie::getBindAtt()
{
	vector<BindAttrib> vec;

	BindAttrib bind0;
	bind0.bindID=0;
	bind0.bindattribute="v1";
	vec.push_back(bind0);

	BindAttrib bind1;
	bind1.bindID=1;
	bind1.bindattribute="v2";
	vec.push_back(bind1);

	BindAttrib bind2;
	bind2.bindID=2;
	bind2.bindattribute="v3";
	vec.push_back(bind2);

	BindAttrib bind3;
	bind3.bindID=3;
	bind3.bindattribute="v4";
	vec.push_back(bind3);

	BindAttrib bind4;
	bind4.bindID=4;
	bind4.bindattribute="boneId";
	vec.push_back(bind4);

	BindAttrib bind5;
	bind5.bindID=5;
	bind5.bindattribute="boneWeight";
	vec.push_back(bind5);

	BindAttrib bind6;
	bind6.bindID=6;
	bind6.bindattribute="texcoord";
	vec.push_back(bind6);

	return vec;
}

string Display3dMovie::getShaderName()
{
	return "display3dmovie_shader";
}

string Display3dMovie::getShadowShaderName()
{
	return "display3dmovieshadow_shader";
}

void Display3dMovie::initData()
{
	meshList = new vector<MeshData*>;
	actionDic = new map<string,AnimData*>;

	_frame = 0;
	_time = 0;
}

void Display3dMovie::setVa()
{
	
}

void Display3dMovie::setVc()
{
	
	posMatrix->identity();
	float pi = 3.1415926;
	Quaternion q(Vector3(0,1,0),_rotationY*pi/180);

	Vector3 pos = Engine::getCamera()->math2dto3d(_x + Engine::getScene()->getX(),_z + + Engine::getScene()->getY()); 

	posMatrix->setTransform(pos,q,Vector3(0.1,0.1,0.1));
	GLuint _projectionSlot = glGetUniformLocation(program, "modelView");
	glUniformMatrix4fv(_projectionSlot,1,GL_FALSE,&(posMatrix->M[0][0]));

	Matrix *camera = Engine::getCamera()->cameraMatrix;
	_projectionSlot = glGetUniformLocation(program, "camera");
	glUniformMatrix4fv(_projectionSlot,1,GL_FALSE,&(camera->M[0][0]));


}

void Display3dMovie::draw()
{

}

void Display3dMovie::update()
{
	glUseProgram(program);
	setVc();
	for(int i=0;i<meshList->size();i++){
		updateTexture((*meshList)[i]);
		updateMesh((*meshList)[i]);
	}

	//updateShadow();
}

void Display3dMovie::addMesh(const string &url ,const string &textureurl)
{
	MeshData *m = Engine::getMeshManager()->getMesh(url);
	if(m == NULL){
		return;
	}
	m->texture = Engine::getTextureManager()->getPngTexture(textureurl);
	meshList->push_back(m);
}

void Display3dMovie::meshComplete(MeshData *mesh)
{
	
}

void Display3dMovie::addAction( const char* actionName,const string &url )
{
	AnimData *a = Engine::getAnimManger()->getAnim(url);

	actionDic->insert(make_pair(actionName,a));
}

void Display3dMovie::play( string action ,int $completeState)
{
	if(isLock){
		return;
	}
	_action = action;
	_completeState = $completeState;
	_frame = 0;
	_time = 0;
	updateTime(0);
}

void Display3dMovie::updateMesh( MeshData *meshData )
{
	AnimData *current = (*actionDic)[_action];

	glBindBuffer(GL_ARRAY_BUFFER,meshData->vertexBuffer1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0,0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,meshData->vertexBuffer2);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,0,0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER,meshData->vertexBuffer3);
	glVertexAttribPointer(2,3, GL_FLOAT, GL_FALSE,0,0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER,meshData->vertexBuffer4);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,0,0);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER,meshData->boneIdBuffer);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE,0,0);
	glEnableVertexAttribArray(4);

	glBindBuffer(GL_ARRAY_BUFFER,meshData->boneWeightBuffer);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE,0,0);
	glEnableVertexAttribArray(5);

	glBindBuffer(GL_ARRAY_BUFFER,meshData->uvBuffer);
	glVertexAttribPointer(6, 2, GL_FLOAT, GL_FALSE,0,0);
	glEnableVertexAttribArray(6);

	vector<int> *boneId = meshData->boneNewIDAry;
	
	for(int j=0;j<boneId->size();j++){
		string name;
		//name += "bone["+to_string((long long)j)+"]";
		name += "bone[" + StringUtils::int2str(j) + "]";
		GLuint _boneSlot = glGetUniformLocation(program, name.c_str());
		Matrix *m0=current->GetData()[_frame][(*boneId)[j]];

		glUniformMatrix4fv(_boneSlot,1,GL_FALSE,&(m0->M[0][0]));

	}
	

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,meshData->IndexBuffer);
	glDrawElements(GL_TRIANGLES,meshData->indexNum, GL_UNSIGNED_SHORT, 0);

}

void Display3dMovie::updateTime( int t )
{
	_time += t;

	AnimData *current = (*actionDic)[_action];

	if(current != NULL){
		_frame = _time/(1000.0f/30.0f);

		if(_frame >= current->GetData().size()){
			if(_completeState == 1){
				_action = "stand";
				isLock = false;
			}
			_frame = 0;
			_time = 0;
		}
		//trace(_frame);
	}

	if(speedX !=0 || speedZ != 0){
		_x += speedX*t;
		_z += speedZ*t;

	}

	
}

void Display3dMovie::updateTexture( MeshData *meshData )
{
	//return;
	GLuint _textureSlot = glGetUniformLocation(program, "tex0");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, meshData->texture);
	glUniform1i(_textureSlot, 0);
}

void Display3dMovie::updateShadow()
{
	glUseProgram(shadowProgram);
	setVc();
	for(int i=0;i<meshList->size();i++){
		updateMesh((*meshList)[i]);
	}
}



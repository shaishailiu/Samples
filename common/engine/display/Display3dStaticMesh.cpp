#include "Engine.h"
#include "analysis/StaticMeshManager.h"
#include "texture/TextureManager.h"
#include "vo/ObjData.h"
#include "utils/Camera3D.h"
#include "math/Core.h"
#include "Display3dStaticMesh.h"


Display3dStaticMesh::Display3dStaticMesh()
{
}


Display3dStaticMesh::~Display3dStaticMesh()
{
}

void Display3dStaticMesh::setVa()
{
	glBindBuffer(GL_ARRAY_BUFFER, objData->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, objData->uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, objData->normalBuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
}

void Display3dStaticMesh::setVc()
{
	GLuint _textureSlot = glGetUniformLocation(program, "tex0");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, objData->texture);
	glUniform1i(_textureSlot, 0);

	posMatrix->identity();
	posMatrix->appendScale(_scale);
	posMatrix->appendRotationAxis(_rotation.X, Vector3::Y_AXIS);
	//posMatrix->appendRotationAxis(_rotation.Y, Vector3::X_AXIS);
	//posMatrix->appendRotationAxis(_rotation.Z, Vector3::Z_AXIS);
	posMatrix->appendTranslation(_position);

	rotationMatrix.identity();
	rotationMatrix.appendRotationAxis(_rotation.X, Vector3::Y_AXIS);
	
	GLuint _projectionSlot = glGetUniformLocation(program, "modelView");
	glUniformMatrix4fv(_projectionSlot, 1, GL_FALSE, &(posMatrix->M[0][0]));

	_projectionSlot = glGetUniformLocation(program, "rotationMat");
	glUniformMatrix4fv(_projectionSlot, 1, GL_FALSE, &(rotationMatrix.M[0][0]));

	Matrix *camera = Engine::getCamera()->cameraMatrix;
	_projectionSlot = glGetUniformLocation(program, "camera");
	glUniformMatrix4fv(_projectionSlot, 1, GL_FALSE, &(camera->M[0][0]));

	_projectionSlot = glGetUniformLocation(program, "light");

	Vector3 lightVec(1, 1, 1);
	lightVec.normalize();

	GLfloat light[4] = { lightVec.X, lightVec.Y, lightVec.Z, 0};
	glUniform4fv(_projectionSlot, 1, light);

	//GLfloat light[3] = { lightVec.X, lightVec.Y, lightVec.Z};
	//glUniform3fv(_projectionSlot, 1, light);
}



std::string Display3dStaticMesh::getShaderName()
{
	return "display3dstaticmesh_shader";
}

std::vector<BindAttrib> Display3dStaticMesh::getBindAtt()
{
	vector<BindAttrib> vec;

	BindAttrib bind0;
	bind0.bindID = 0;
	bind0.bindattribute = "position";
	vec.push_back(bind0);


	BindAttrib bind1;
	bind1.bindID = 1;
	bind1.bindattribute = "texcoord";
	vec.push_back(bind1);

	BindAttrib bind2;
	bind2.bindID = 2;
	bind2.bindattribute = "normal";
	vec.push_back(bind2);

	return vec;
}

void Display3dStaticMesh::setObjUrl(const string &url, const string &textureurl)
{
	objData = Engine::getEngine()->getStaticMeshManager()->getMesh(url);
	objData->texture = Engine::getEngine()->getTextureManager()->getPngTexture(textureurl);
}

void Display3dStaticMesh::draw()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objData->IndexBuffer);
	glDrawElements(GL_TRIANGLES, objData->indexNum, GL_UNSIGNED_SHORT, 0);
}

#include "log/LogTrace.h"
#include "vo/ObjData.h"
#include "utils/Memory.h"
#include "utils/FileUtils.h"
#include "StaticMeshManager.h"


StaticMeshManager::StaticMeshManager()
{
}


StaticMeshManager::~StaticMeshManager()
{
}

ObjData * StaticMeshManager::getMesh(string fileUrl)
{
	Memory *memory = FileUtils::loadFile(fileUrl.c_str());

	if (memory == NULL){
		return NULL;
	}

	int vecticesLength = memory->readInt();
	vector<GLfloat> vectices;
	for (int i = 0; i < vecticesLength; i++)
	{
		vectices.push_back(memory->readFloat());
	}

	int normalsLength = memory->readInt();
	vector<GLfloat> normals;
	for (int i = 0; i < normalsLength; i++)
	{
		normals.push_back(memory->readFloat());
	}

	int uvLength = memory->readInt();
	vector<GLfloat> uvs;
	for (int i = 0; i < uvLength; i++)
	{
		uvs.push_back(memory->readFloat());
	}

	int uv2Length = memory->readInt();
	vector<GLfloat> uv2s;
	for (int i = 0; i < uv2Length; i++)
	{
		uv2s.push_back(memory->readFloat());
	}

	int indexsLength = memory->readInt();
	vector<GLshort> indexs;
	for (int i = 0; i < indexsLength; i++)
	{
		indexs.push_back(memory->readInt());
	}

	delete memory;

	ObjData *objData = new ObjData();

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vectices.size() * sizeof(GLfloat), (void *)&vectices[0], GL_STATIC_DRAW);
	objData->vertexBuffer = vertexBuffer;

	GLuint normalBuffer;
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), (void *)&normals[0], GL_STATIC_DRAW);
	objData->normalBuffer = normalBuffer;

	GLuint uvBuffer;
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(GLfloat), (void *)&uvs[0], GL_STATIC_DRAW);
	objData->uvBuffer = uvBuffer;

	GLuint uv2Buffer;
	glGenBuffers(1, &uv2Buffer);
	glBindBuffer(GL_ARRAY_BUFFER, uv2Buffer);
	glBufferData(GL_ARRAY_BUFFER, uv2s.size() * sizeof(GLfloat), (void *)&uv2s[0], GL_STATIC_DRAW);
	objData->uv2Buffer = uv2Buffer;


	GLuint IndexBuffer;
	glGenBuffers(1, &IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexs.size() * sizeof(GLushort), (void *)&indexs[0], GL_STATIC_DRAW);
	objData->IndexBuffer = IndexBuffer;
	objData->indexNum = indexs.size();

	return objData;
}

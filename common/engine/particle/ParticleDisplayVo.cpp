#include "ParticleDisplayVo.h"


ParticleDisplayVo::ParticleDisplayVo(void)
{
}


ParticleDisplayVo::~ParticleDisplayVo(void)
{
}

void ParticleDisplayVo::setDataByJson( const Json::Value vo )
{
	particleType = vo["particleType"].asInt();
	width = vo["width"].asDouble();
	height = vo["height"].asDouble();
	tileMode = vo["tileMode"].asBool();
	widthFixed = vo["widthFixed"].asBool();
	heightFixed = vo["heightFixed"].asBool();
	originWidthScale = vo["originWidthScale"].asDouble();
	originHeightScale = vo["originHeightScale"].asDouble();
	isCycle = vo["isCycle"].asBool();
	speed = vo["speed"].asDouble();
	uSpeed = vo["uSpeed"].asDouble();
	vSpeed = vo["vSpeed"].asDouble();
	textureUrl = vo["textureUrl"].asString();
	maskUrl = vo["maskUrl"].asString();
	renderPriority = vo["renderPriority"].asInt();
	animLine = vo["animLine"].asInt();
	animRow = vo["animRow"].asInt();
	animInterval = vo["animInterval"].asInt();
	eyeDistance = vo["eyeDistance"].asInt();
	alphaMode = vo["alphaMode"].asInt();
	life = vo["life"].asInt();
	watchEye = vo["watchEye"].asBool();
	closeGround = vo["closeGround"].asBool();
	gormalsGround = vo["gormalsGround"].asBool();

	isU = vo["isU"].asBool();
	isV = vo["isV"].asBool();
	isUV = vo["isUV"].asBool();

	rotationX = vo["rotationX"].asDouble();
	rotationY = vo["rotationY"].asDouble();
	rotationZ = vo["rotationZ"].asDouble();

	center = getVec3(vo["center"]);
	overAllScale = vo["overAllScale"].asDouble();

	/**************************/
	totalNum = vo["totalNum"].asInt();
	acceleration = vo["acceleration"].asDouble();
	toscale = vo["toscale"].asDouble();
	timeRandom = vo["timeRandom"].asBool();
	qishijuli = vo["qishijuli"].asDouble();
	lockY = vo["lockY"].asBool();
	lockX = vo["lockX"].asBool();
	isLoop = vo["isLoop"].asBool();
	shootAngly = getVec4(vo["shootAngly"]);
	shootSpeed = vo["shootSpeed"].asDouble();
	shootInterval = vo["shootInterval"].asDouble();
	isRandom = vo["isRandom"].asBool();
	isSendRandom = vo["isSendRandom"].asBool();
	isSendAngleRandom = vo["isSendAngleRandom"].asBool();
	ziZhuanAngly = getVec4(vo["ziZhuanAngly"]);
	addforce = getVec4(vo["addforce"]);
	lixinForce = getVec4(vo["lixinForce"]);
	waveform = getVec4(vo["waveform"]);
	round = getVec4(vo["round"]);
	is3Dlizi = vo["is3Dlizi"].asBool();
	gezhiDuanshu = vo["gezhiDuanshu"].asDouble();
	closeSurface = vo["closeSurface"].asBool();
	isEven = vo["isEven"].asBool();
	basePositon = getVec3(vo["basePositon"]);
	baseRandomAngle = vo["baseRandomAngle"].asDouble();
	shapeType = vo["shapeType"].asInt();
	fasanJiaodu = vo["fasanJiaodu"].asInt();
	paticleMinScale = vo["paticleMinScale"].asDouble();
	paticleMaxScale = vo["paticleMaxScale"].asDouble();
	islixinAngly = vo["islixinAngly"].asBool();
	particleRandomScale = getVec3(vo["particleRandomScale"]);


	fenduanshu = vo["fenduanshu"].asInt();
	qingxiejiaodu = vo["qingxiejiaodu"].asDouble();
	isCenter = vo["isCenter"].asBool();

	/**************************/
	widthScale = vo["widthScale"].asDouble();
	faceNum = vo["faceNum"].asInt();

	/**************************/
	maxAnimTime = vo["maxAnimTime"].asInt();


	/**************************/
	objUrl = vo["objUrl"].asString();
	objScale = vo["objScale"].asDouble();

	/**************************/
	beginVector3D = getVec3(vo["beginVector3D"]);
	endVector3D = getVec3(vo["endVector3D"]);
	density = vo["density"].asInt();

	/**************************/
	meshUrl = vo["meshUrl"].asString();
	animUrl = vo["animUrl"].asString();
	depthMode = vo["depthMode"].asBool();
	playSpeed = vo["playSpeed"].asDouble();

	textureColor.setDataByJson(vo["textureColor"],false);
	randomColor.setDataByJson(vo["randomColor"],true);

	addforce.X *= addforce.W;
	addforce.Y *= addforce.W;
	addforce.Z *= addforce.W;

}

Vector4 ParticleDisplayVo::getVec4( const Json::Value v4d )
{
	Vector4 vec4;
	vec4.X = v4d["x"].asDouble();
	vec4.Y = v4d["y"].asDouble();
	vec4.Z = v4d["z"].asDouble();
	vec4.W = v4d["w"].asDouble();
	return vec4;
}

Vector3 ParticleDisplayVo::getVec3( const Json::Value v3d )
{
	Vector3 vec3;
	vec3.X = v3d["x"].asDouble();
	vec3.Y = v3d["y"].asDouble();
	vec3.Z = v3d["z"].asDouble();
	return vec3;

}

attribute vec4 vPosition;

attribute vec3 texcoord;//uv坐标xyz，随机数w

attribute vec4 basePos;//基础位置xyz，发射起始时间w

attribute vec4 speed;//速度xyz，基础旋转w

uniform mat4 watheye;//面向视点矩阵
uniform mat4 modelView;//模型矩阵
uniform mat4 camera;//摄像机矩阵
uniform vec4 time;//当前时间x,自身加速度y,粒子生命z,是否循环w
uniform vec4 force;//外力x，外力y，外力z，0
uniform vec4 scale;//缩放x，抖动周期y，抖动振幅z，1
uniform vec4 scaleCtrl;//宽度不变，高度不变，最大比例，最小比例
uniform vec4 animCtrl;//动画行数x，动画列数，动画间隔，未使用
uniform vec4 uvCtrl;//u滚动速度，v滚动速度，是否使用颜色渐变，是否使用随机颜色

varying vec4 texcoord0;
varying vec4 texcoord1;

void main()
{
	//计算当前时间
	float ctime = time.x - basePos.w;
	if(time.w > 0.0 && ctime >= 0.0){
		ctime = fract(ctime/time.z) * time.z;
	}

	//自身变化部分
	vec4 pos = vPosition;

	float sf = scale.x * ctime;
	if(scale.y != 0.0 && scale.z != 0.0){
		sf += sin(scale.y * ctime) * scale.z;
	}

	if(sf != 0.0){
		if(sf > scaleCtrl.z){
			sf = scaleCtrl.z;
		}else if(sf < scaleCtrl.w){
			sf = scaleCtrl.w;
		}

		vec2 sv2 = vec2(scaleCtrl.x * sf,scaleCtrl.y * sf);
		sv2 = sv2 + scale.w;
		pos.x *= sv2.x;
		pos.y *= sv2.y;
	}

	if(speed.w != 0.0){
		vec4 np = vec4(sin(speed.w),cos(speed.w),0,0);
		np.z = np.x * pos.y + np.y * pos.x;//b.x = sin_z * a.y + cos_z * a.x;
		np.w = np.y * pos.y - np.x * pos.x;//b.y = cos_z * a.y - sin_z * a.x;
		pos.xy = np.zw;
	}
	
	pos = watheye * pos; //控制是否面向视点

	//运动部分
	vec4 addPos = speed * ctime;

	vec3 uspeed; 
	if(time.y != 0.0 && length(uspeed) != 0.0){
		uspeed = vec3(speed.x,speed.y,speed.z);
		uspeed = normalize(uspeed);
		uspeed = uspeed * time.y;
		uspeed.xyz = uspeed.xyz + force.xyz;
	}else{
		uspeed = vec3(force.x,force.y,force.z);
	}
	
	addPos.xyz = addPos.xyz + uspeed.xyz * ctime * ctime;

	//根据时间控制粒子是否显示
	if(ctime < 0.0 || ctime >= time.z){
		addPos.y = addPos.y + 100000.0;
	}

	pos.xyz = pos.xyz + basePos.xyz + addPos.xyz;

	gl_Position = camera * modelView * pos;

	//uv控制部分
	texcoord0 = vec4(texcoord.x,texcoord.y,uvCtrl.z,uvCtrl.w);

	if(animCtrl.x != 1.0 && animCtrl.y != 1.0){
		vec2 uv = vec2(texcoord.x,texcoord.y);
		float animframe = floor(ctime/animCtrl.z);
		animframe = animframe/animCtrl.x;
		uv.x += animframe;
		animframe = floor(animframe);
		uv.y += animframe/animCtrl.y;
		uv.y = 1.0 - uv.y;
		texcoord0.xy = uv.xy;
	}else if(uvCtrl.x != 0.0 || uvCtrl.y != 0.0){
		vec2 uv = vec2(uvCtrl.x,uvCtrl.y);
		uv.xy = uv.xy * ctime + texcoord.xy;
		uv.y = 1.0 - uv.y;
		texcoord0.xy = uv.xy;
	}
	//粒子颜色部分
	texcoord1 = vec4(ctime/time.z,1.0,texcoord.z,0.5);

}

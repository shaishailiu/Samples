attribute vec4 vPosition;

attribute vec3 texcoord;//uv����xyz�������w

attribute vec4 basePos;//����λ��xyz��������ʼʱ��w

attribute vec4 speed;//�ٶ�xyz��������תw

uniform mat4 watheye;//�����ӵ����
uniform mat4 modelView;//ģ�;���
uniform mat4 camera;//���������
uniform vec4 time;//��ǰʱ��x,������ٶ�y,��������z,�Ƿ�ѭ��w
uniform vec4 force;//����x������y������z��0
uniform vec4 scale;//����x����������y���������z��1
uniform vec4 scaleCtrl;//��Ȳ��䣬�߶Ȳ��䣬����������С����
uniform vec4 animCtrl;//��������x���������������������δʹ��
uniform vec4 uvCtrl;//u�����ٶȣ�v�����ٶȣ��Ƿ�ʹ����ɫ���䣬�Ƿ�ʹ�������ɫ

varying vec4 texcoord0;
varying vec4 texcoord1;

void main()
{
	//���㵱ǰʱ��
	float ctime = time.x - basePos.w;
	if(time.w > 0.0 && ctime >= 0.0){
		ctime = fract(ctime/time.z) * time.z;
	}

	//����仯����
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
	
	pos = watheye * pos; //�����Ƿ������ӵ�

	//�˶�����
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

	//����ʱ����������Ƿ���ʾ
	if(ctime < 0.0 || ctime >= time.z){
		addPos.y = addPos.y + 100000.0;
	}

	pos.xyz = pos.xyz + basePos.xyz + addPos.xyz;

	gl_Position = camera * modelView * pos;

	//uv���Ʋ���
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
	//������ɫ����
	texcoord1 = vec4(ctime/time.z,1.0,texcoord.z,0.5);

}

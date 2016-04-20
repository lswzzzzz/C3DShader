#ifdef GL_ES
varying lowp vec2 v_texCoord;
varying lowp vec3 v_normal;
varying lowp vec3 v_worldpos;
#else
varying vec2 v_texCoord;
varying vec3 v_normal;
varying vec3 v_worldpos;
#endif

uniform vec3 u_LightDir;
uniform vec3 u_EyePos;

void main()
{
	vec3 normal = normalize(v_normal);
	//光的方向
	vec3 lightDir = normalize(u_LightDir);
	//相机的观察方向
	vec3 viewDir = normalize(u_EyePos-v_worldpos);
	//光与法线 的颜色关系
	float fDiff = clamp(dot(v_normal, -lightDir), 0.2, 1.0);
	vec4 texColor = texture2D(CC_Texture0, v_texCoord);
	//反射先写入射方向 再写法线
	vec3 reflect = normalize(reflect(lightDir, v_normal));
	vec4 specularColor = vec4(1.0, 1.0, 1.0, 1.0);
	//镜面反射公式镜面反射方向和物体朝相机的方向越近，系数越大
	float specular = pow(clamp(dot(viewDir, reflect), 0, 1.0), 10);
	gl_FragColor = texColor * fDiff + specularColor * specular;
	gl_FragColor.a = texColor.a;
}
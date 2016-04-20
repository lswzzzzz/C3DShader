#ifdef GL_ES
varying lowp vec2 v_texCoord;
varying lowp vec3 v_worldpos;
#else
varying vec2 v_texCoord;
varying vec3 v_worldpos;
#endif

uniform vec3 u_PointLightPositionArray[3];
uniform float u_PointLightRange[3];
uniform vec3 u_PointLightColorArray[3];

vec4 getLightColor(vec3 vPos)
{
	vec3 v_color = vec3(0.0, 0.0, 0.0);
	for(int i=0; i<3; i++){
		vec3 Dir = u_PointLightPositionArray[i] - vPos;
		float fLerp = 1.0 - clamp(length(Dir)/u_PointLightRange[i], 0, 1.0);
		v_color += u_PointLightColorArray[i] * fLerp;
	}
	return vec4(v_color, 1.0);
}

void main()
{
	vec4 texColor = texture2D(CC_Texture0, v_texCoord);
	gl_FragColor = texColor * getLightColor(v_worldpos);
	gl_FragColor.a = texColor.a;	
}
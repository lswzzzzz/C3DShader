#ifdef GL_ES
varying mediump vec2 v_texCoord;
varying mediump vec4 v_fragmentColor;
varying mediump vec2 v_position;
#else
varying vec2 v_texCoord;
varying vec4 v_fragmentColor;
varying vec2 v_position;
#endif

uniform vec2	LightPos[2];
uniform float	LightRange[2];
uniform vec4    LightColor[2];

vec4 GetLightColor(vec2 vPos, vec2 lightPos, float fRange)
{
	//light direction
	vec2 lightdirection = vPos - lightPos;
	float distance = length(lightdirection);
	float l = distance / fRange;
	l = 1.0 - clamp(l, 0, 1.0);
	return vec4(l, l, l, 1);
}

void main()
{
	vec4 LightColor = LightColor[0] * GetLightColor(v_position, LightPos[0], LightRange[0])
					+ LightColor[1] * GetLightColor(v_position, LightPos[1], LightRange[1]);
	LightColor = clamp(LightColor, 0, 1.0);
	gl_FragColor = texture2D(CC_Texture0, v_texCoord) * v_fragmentColor * LightColor;
}
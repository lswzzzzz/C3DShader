#ifdef GL_ES
varying lowp vec2 v_texCoord;
varying lowp vec3 v_normal;
#else
varying vec2 v_texCoord;
varying vec3 v_normal;
#endif

uniform vec3 u_LightDir;

void main()
{
    vec4 TexColor = texture2D(CC_Texture0, v_texCoord);
	float fDiff = clamp(dot(v_normal, -u_LightDir), 0.2, 1.0);
	gl_FragColor = TexColor * fDiff;
	gl_FragColor.a = TexColor.a;
}

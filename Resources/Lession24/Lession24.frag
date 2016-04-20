#ifdef GL_ES
varying lowp vec2 v_texCoord;
#else
varying vec2 v_texCoord;
#endif

uniform sampler2D u_Texture;

void main()
{
	float alphaColor = texture2D(u_Texture, v_texCoord).r;
	if(alphaColor < 0.3) discard;
	gl_FragColor = texture2D(CC_Texture0, v_texCoord);
	gl_FragColor.a = alphaColor;
}
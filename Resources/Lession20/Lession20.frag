#ifdef GL_ES
varying lowp vec2 v_texCoord;
#else
varying vec2 v_texCoord;
#endif
uniform sampler2D   u_MaskTexture;
uniform vec4		u_EyeColor;
void main()
{
	vec4    tTexColor  = texture2D(CC_Texture0,v_texCoord );
	vec4    tMaskColor = texture2D(u_MaskTexture,v_texCoord) ;
	if(tMaskColor.r > 0)
	{
		gl_FragColor = u_EyeColor ;
	}
	else
	{
		gl_FragColor = tTexColor ;
	}
}

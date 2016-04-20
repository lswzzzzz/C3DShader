#ifdef GL_ES
varying lowp vec2 v_texCoord;
#else
varying vec2 v_texCoord;
#endif

void main()
{
	gl_FragColor = texture2D(CC_Texture0, v_texCoord+vec2(CC_Time.x, 0));
}
attribute vec4 a_position;
attribute vec2 a_texCoord;

#ifdef GL_ES
varying lowp vec2 v_texCoord;
#else
varying vec2 v_texCoord;
#endif

void main()
{
	gl_Position = CC_MVPMatrix * a_position;
	v_texCoord = a_texCoord;
	v_texCoord.y = 1.0 - v_texCoord.y;
}

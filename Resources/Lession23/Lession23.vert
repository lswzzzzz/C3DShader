attribute vec4 a_position;
attribute vec2 a_texCoord;

#ifdef GL_ES
varying lowp vec2 v_texCoord;
varying lowp vec3 v_worldpos;
#else
varying vec2 v_texCoord;
varying vec3 v_worldpos;
#endif

uniform mat4 u_WorldMatrix;

void main()
{
	gl_Position = CC_MVPMatrix * a_position;
	v_worldpos = (u_WorldMatrix * a_position).xyz;
	v_texCoord = a_texCoord;
}
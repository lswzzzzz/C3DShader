attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec2 a_texCoord;

#ifdef GL_ES
varying lowp vec2 v_texCoord;
varying lowp vec3 v_normal;
varying lowp vec3 v_worldpos;
#else
varying vec2 v_texCoord;
varying vec3 v_normal;
varying vec3 v_worldpos;
#endif

uniform mat4 u_WorldMatrix;

void main()
{
	gl_Position = CC_MVPMatrix * a_position;
	v_normal = CC_NormalMatrix * a_normal;
	v_worldpos = (u_WorldMatrix * a_position).xyz;
	v_texCoord = a_texCoord;
}
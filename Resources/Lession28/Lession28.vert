attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec2 a_texCoord;
attribute vec3 a_tangent;
attribute vec3 a_bitangent;

#ifdef GL_ES											
varying mediump vec3 v_normal;
varying mediump vec2 v_texCoord;
varying mediump vec3 v_tangent;
varying mediump vec3 v_bitangent;
varying mediump vec3 v_worldpos;
#else														
varying vec3 v_normal;
varying vec2  v_texCoord;	
varying vec3 v_tangent;
varying vec3 v_bitangent;
varying vec3  v_worldpos;
#endif

void main()												
{	
	vec4	tWorldPosition	= CC_MVMatrix * a_position ;
	v_worldpos				= tWorldPosition.xyz;
    gl_Position				= CC_MVPMatrix * a_position;
	v_texCoord				= a_texCoord;
	v_normal				= a_normal;
	v_tangent				= a_tangent;
	v_bitangent				= a_bitangent;
}														

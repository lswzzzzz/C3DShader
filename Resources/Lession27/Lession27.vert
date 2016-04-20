attribute vec4 a_position;
attribute vec3 a_normal;

varying vec3 v_reflect;

void main(void)
{
    gl_Position = CC_MVPMatrix * a_position;
	vec4 worldpos = CC_MVMatrix * a_position;
	vec3 eyepos = normalize(worldpos.xyz);
	vec3 normal = CC_NormalMatrix * a_normal;
	v_reflect = normalize(reflect(-eyepos, normal));
}

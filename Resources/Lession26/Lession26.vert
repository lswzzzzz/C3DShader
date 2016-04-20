attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec3 a_normal;

#ifdef GL_ES
varying mediump vec2 v_texCoord;
varying float v_fogFactor;
#else
varying vec2 v_texCoord;
varying float v_fogFactor;
#endif

uniform float u_fogStart;
uniform float u_fogEnd;
uniform float u_fogDensity;
uniform int u_fogEquation;

void main()
{
	gl_Position = CC_MVPMatrix * a_position;

	float fogFragCoord = abs(gl_Position.z);

	if(u_fogEquation == 0){
		v_fogFactor = (u_fogEnd - fogFragCoord) / (u_fogEnd - u_fogStart);
	}else if(u_fogEquation == 1){
		v_fogFactor = exp(-u_fogDensity * fogFragCoord);
	}else{
		v_fogFactor = exp(pow(u_fogDensity * fogFragCoord, 2.0));
	}
	v_texCoord = a_texCoord;
	v_fogFactor = clamp(v_fogFactor, 0, 1.0);
}
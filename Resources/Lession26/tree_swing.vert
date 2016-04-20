attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec3 a_normal;

#ifdef GL_ES
varying mediump vec2 v_texCoord;
varying mediump float v_fogFactor;              //weight for fog
#else
varying vec2 v_texCoord;
varying float v_fogFactor;              //weight for fog
#endif

uniform float u_fogDensity;// For exp and exp2 equation
uniform float u_fogStart; // This is only for linear fog
uniform float u_fogEnd; // This is only for linear fog
uniform int u_fogEquation; // 0 = linear, 1 = exp, 2 = exp2

uniform   float uSwingRange;
uniform vec4 u_color;

vec3 SwingVectex(float curTime, float swingSpeed)
{
	float timefactor = curTime * swingSpeed;
	vec3 posOffset = vec3(cos(timefactor)*uSwingRange, 0, sin(timefactor)*uSwingRange);
	return posOffset;	
}

void main(void)
{
   vec3 offset = SwingVectex(CC_Time.y, a_position.y*0.01);
   vec4 position = vec4(a_position.x + offset.x, a_position.y, a_position.z + offset.z, a_position.w);
   gl_Position = CC_MVPMatrix * position;
	
    v_texCoord = a_texCoord;
	
	float fogFragCoord = abs(gl_Position.z);                                       //get fog distance

    if(u_fogEquation == 0)
            v_fogFactor = (u_fogEnd-fogFragCoord )/(u_fogEnd-u_fogStart);                //linear fog
    else if(u_fogEquation == 1)
            v_fogFactor = exp(-u_fogDensity*fogFragCoord  );                         //exp fog
    else if(u_fogEquation == 2)
	    v_fogFactor = exp(-pow(u_fogDensity*fogFragCoord , 2.0));                //exp2 fog


    v_fogFactor = clamp(v_fogFactor, 0.0, 1.0);                                     //clamp 0 to 1
}

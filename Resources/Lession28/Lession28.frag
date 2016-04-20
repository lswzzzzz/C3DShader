
uniform vec3		EyePos;
uniform vec3		LightDir;
uniform float		SpecularPower;
uniform float		SpecularLevel;

uniform mat4		matRotate;
uniform sampler2D	CC_Texture_Bump;	


#ifdef GL_ES											
//varying mediump vec3 v_color;	
varying mediump vec2 v_texCoord;
varying mediump vec3 v_normal;
varying mediump vec3 v_tangent;
varying mediump vec3 v_bitangent;
varying mediump vec3 v_worldpos;
#else													
//varying vec3 v_color;	
varying vec2 v_texCoord;	
varying vec3 v_normal;
varying vec3 v_tangent;
varying vec3 v_bitangent;
varying vec3 v_worldpos;
#endif

void main()
{	

	vec4 texColor = texture2D(CC_Texture0, v_texCoord);
	vec3 eyedir = v_worldpos - EyePos;
	eyedir = normalize(eyedir);

	vec3 bumpColor = texture2D(CC_Texture_Bump, v_texCoord).xyz;
	vec3 btnnormal = normalize(2 * bumpColor - 1);
	
	float diffusefactor = max(0, dot(btnnormal, LightDir));
	float specularfactor = abs(dot(eyedir, btnnormal));
	specularfactor = pow(specularfactor, 10);

	float amb = 0.2;
	float diff = 0.5;
	float spec = 0.3;
	vec4 diffuseColor = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 ambientColor = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 specularColor = vec4(1.0, 1.0, 1.0, 1.0);
	gl_FragColor = (amb * ambientColor + diffuseColor * diff * diffusefactor) * texColor +
			spec * specularfactor * specularColor;
}																		

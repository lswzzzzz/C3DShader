#ifdef GL_ES
varying mediump vec2 v_texCoord;
varying lowp vec4 v_color;
#else
varying vec2 v_texCoord;
varying vec4 v_color;
#endif

uniform vec2 TexSize;
uniform float 	PI;
uniform float 	sigma2;

float getWeight(vec2 pos)
{
	return exp(-(pos.x*pos.x+pos.y*pos.y)/sigma2) / (sigma2 * PI);
}

vec4 getWeightColor(vec2 pos, vec4 color)
{
	float weight = getWeight(pos);
	return vec4(color.r*weight, color.g*weight, color.b*weight, color.a);
}

void main()
{
	float dx = 1.0/float(TexSize.x);
     float dy = 1.0/float(TexSize.y);
	//vec4 color = getWeightColor(vec2(-1, -1), texture2D(CC_Texture0,v_texCoord.xy+vec2(-dx, -dy)));
   //color += getWeightColor(vec2(0, -1), texture2D(CC_Texture0,v_texCoord.xy+vec2(0.0, -dy)));
	//color += getWeightColor(vec2(1, -1), texture2D(CC_Texture0,v_texCoord.xy+vec2(dx, -dy)));

	 //color += getWeightColor(vec2(-1, 0), texture2D(CC_Texture0,v_texCoord.xy+vec2(-dx, 0.0)));
	 //color += getWeightColor(vec2(0, 0), texture2D(CC_Texture0,v_texCoord.xy+vec2(0.0, 0.0)));
	 //color += getWeightColor(vec2(1, 0), texture2D(CC_Texture0,v_texCoord.xy+vec2(dx, 0.0)));

	//color += getWeightColor(vec2(-1, 1), texture2D(CC_Texture0,v_texCoord.xy+vec2(-dx, dy)));
	//color += getWeightColor(vec2(0, 1), texture2D(CC_Texture0,v_texCoord.xy+vec2(0.0, dy)));
	//color += getWeightColor(vec2(1, 1), texture2D(CC_Texture0,v_texCoord.xy+vec2(dx, dy)));


	vec4 color;
	 color = getWeightColor(vec2(-2, -2), texture2D(CC_Texture0,v_texCoord.xy+vec2(-dx*2, -dy*2)));
	 color += getWeightColor(vec2(-1, -2), texture2D(CC_Texture0, v_texCoord.xy + vec2(-dx, -dy * 2)));
	color += getWeightColor(vec2(1, -2), texture2D(CC_Texture0, v_texCoord.xy + vec2(0, -dy * 2)));
	color += getWeightColor(vec2(0, -2), texture2D(CC_Texture0, v_texCoord.xy + vec2(dx, -dy * 2)));
	color += getWeightColor(vec2(1, -2), texture2D(CC_Texture0, v_texCoord.xy + vec2(dx * 2, -dy * 2)));

	color += getWeightColor(vec2(-2, -1), texture2D(CC_Texture0, v_texCoord.xy + vec2(-dx * 2, -dy)));
	color += getWeightColor(vec2(-1, -1), texture2D(CC_Texture0, v_texCoord.xy + vec2(-dx, -dy)));
	color += getWeightColor(vec2(0, -1), texture2D(CC_Texture0, v_texCoord.xy + vec2(0, -dy)));
	color += getWeightColor(vec2(1, -1), texture2D(CC_Texture0, v_texCoord.xy + vec2(dx, -dy)));
	color += getWeightColor(vec2(2, -1), texture2D(CC_Texture0, v_texCoord.xy + vec2(dx * 2, -dy)));

	color += getWeightColor(vec2(-2, 0), texture2D(CC_Texture0, v_texCoord.xy + vec2(-dx * 2, 0.0)));
	color += getWeightColor(vec2(-1, 0), texture2D(CC_Texture0, v_texCoord.xy + vec2(-dx, 0.0)));
	color += getWeightColor(vec2(0, 0), texture2D(CC_Texture0, v_texCoord.xy + vec2(0, 0.0)));
	color += getWeightColor(vec2(1, 0), texture2D(CC_Texture0, v_texCoord.xy + vec2(dx, 0.0)));
	color += getWeightColor(vec2(2, 0), texture2D(CC_Texture0, v_texCoord.xy + vec2(dx * 2, 0.0)));

	color += getWeightColor(vec2(-2, 1), texture2D(CC_Texture0, v_texCoord.xy + vec2(-dx * 2, dy)));
	color += getWeightColor(vec2(-1, 1), texture2D(CC_Texture0, v_texCoord.xy + vec2(-dx, dy)));
	color += getWeightColor(vec2(0, 1), texture2D(CC_Texture0, v_texCoord.xy + vec2(0, dy)));
	color += getWeightColor(vec2(1, 1), texture2D(CC_Texture0, v_texCoord.xy + vec2(dx, dy)));
	color += getWeightColor(vec2(2, 1), texture2D(CC_Texture0, v_texCoord.xy + vec2(dx * 2, dy)));

	color += getWeightColor(vec2(-2, 2), texture2D(CC_Texture0, v_texCoord.xy + vec2(-dx * 2, dy * 2)));
	color += getWeightColor(vec2(-1, 2), texture2D(CC_Texture0, v_texCoord.xy + vec2(-dx, dy * 2)));
	color += getWeightColor(vec2(0, 2), texture2D(CC_Texture0, v_texCoord.xy + vec2(0, dy * 2)));
	color += getWeightColor(vec2(1, 2), texture2D(CC_Texture0, v_texCoord.xy + vec2(dx, dy * 2)));
	color += getWeightColor(vec2(2, 2), texture2D(CC_Texture0, v_texCoord.xy + vec2(dx * 2, dy * 2)));

     gl_FragColor = color;
}
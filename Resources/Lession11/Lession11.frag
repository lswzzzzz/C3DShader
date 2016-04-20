#ifdef GL_ES
varying mediump vec2 v_texCoord;
varying lowp vec4 v_color;
#else
varying vec2 v_texCoord;
varying vec4 v_color;
#endif

uniform vec2 TexSize;

//简单方法
vec4 simpleRelief()
{
	float dx = 1.0/float(TexSize.x);
    float dy = 1.0/float(TexSize.y);
	vec4 color = texture2D(CC_Texture0, v_texCoord) * v_color;
	color *= 8;
	color -= texture2D(CC_Texture0,v_texCoord.xy+vec2(-dx, -dy));
	color -= texture2D(CC_Texture0,v_texCoord.xy+vec2(0, -dy));
	color -= texture2D(CC_Texture0,v_texCoord.xy+vec2(dx, -dy));
	color -= texture2D(CC_Texture0,v_texCoord.xy+vec2(-dx, 0));
	color -= texture2D(CC_Texture0,v_texCoord.xy+vec2(dx, 0));
	color -= texture2D(CC_Texture0,v_texCoord.xy+vec2(-dx, dy));
	color -= texture2D(CC_Texture0,v_texCoord.xy+vec2(0, dy));
	color -= texture2D(CC_Texture0,v_texCoord.xy+vec2(dx, dy));
	color = vec4(color.r+0.5, color.g+0.5, color.b+0.5, 1.0);
	float m;
	m = color.r>color.g?color.r:color.g;
	m = m > color.b?m:color.b;
	color = vec4(m, m, m, 1.0);
	return color;
}

//C3D中的方法这个不是真正的浮雕 是边缘加强而已
vec4 C3DFunction()
{
	vec2 upLeftUV = vec2(v_texCoord.x - 1.0/TexSize.x, v_texCoord.y - 1.0/TexSize.y);
	vec4 bkColor = vec4(0.5, 0.5, 0.5, 1.0);
	vec4 curColor = texture2D(CC_Texture0, v_texCoord)*v_color;
	vec4 upLeftColor = texture2D(CC_Texture0, upLeftUV)*v_color;
	//相减得到颜色的差
	vec4 delColor = curColor - upLeftColor;
	//需要把这个颜色的差设置
	float h = 0.3 * delColor.x + 0.59 * delColor.y + 0.11 * delColor.z;
	vec4 _outColor = vec4(h, h, h, 0.0) + curColor;
	return _outColor;
}

void main()
{
	gl_FragColor = simpleRelief();
}
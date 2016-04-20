#ifdef GL_ES
varying mediump vec2 v_texCoord;
varying lowp vec4 v_color;
#else
varying vec2 v_texCoord;
varying vec4 v_color;
#endif

uniform vec2 TexSize;
uniform vec2 mosaicSize;
uniform int open;
uniform float index;

void main()
{
	//得到当前纹理坐标相对图像大小整数值
	vec2 intXY = vec2(v_texCoord.x * TexSize.x, v_texCoord.y * TexSize.y);
	//根据马赛克块大小进行取整
	vec2 masaicBlockSize = vec2(int(intXY.x/mosaicSize.x)* mosaicSize.x, int(intXY.y/mosaicSize.y) * mosaicSize.y);
	if(open == 1){
		masaicBlockSize = vec2(masaicBlockSize.x+mosaicSize.x*index/2, masaicBlockSize.y+mosaicSize.y*index/2);
	}
	
	//转换回纹理采样坐标
	vec2 UVMosaic = vec2(masaicBlockSize.x/TexSize.x, masaicBlockSize.y/TexSize.y);
	gl_FragColor = texture2D(CC_Texture0, UVMosaic) * v_color;
}
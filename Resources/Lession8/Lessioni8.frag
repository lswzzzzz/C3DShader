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
	//�õ���ǰ�����������ͼ���С����ֵ
	vec2 intXY = vec2(v_texCoord.x * TexSize.x, v_texCoord.y * TexSize.y);
	//���������˿��С����ȡ��
	vec2 masaicBlockSize = vec2(int(intXY.x/mosaicSize.x)* mosaicSize.x, int(intXY.y/mosaicSize.y) * mosaicSize.y);
	if(open == 1){
		masaicBlockSize = vec2(masaicBlockSize.x+mosaicSize.x*index/2, masaicBlockSize.y+mosaicSize.y*index/2);
	}
	
	//ת���������������
	vec2 UVMosaic = vec2(masaicBlockSize.x/TexSize.x, masaicBlockSize.y/TexSize.y);
	gl_FragColor = texture2D(CC_Texture0, UVMosaic) * v_color;
}
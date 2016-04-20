#ifdef GL_ES
varying mediump vec2 v_texCoord;
varying lowp vec4 v_color;
#else
varying vec2 v_texCoord;
varying vec4 v_color;
#endif

uniform vec2 TexSize;

//用来做滤波操作的函数
vec4 dip_filter(mat3 _filter , sampler2D _image, vec2 _xy, vec2 texSize)
{
	//纹理坐标采样的偏移
	vec2 _filter_pos_delta[3][3] = 
	{
		{vec2(-1.0, -1.0), vec2(0, -1.0), vec2(1.0, -1.0)},
		{vec2(0.0, -1.0), vec2(0.0, 0.0), vec2(1.0, 0.0)},
		{vec2(1.0, -1.0), vec2(0, 1.0), vec2(1.0, 1.0)}
	};
	vec4 final_color = vec4(0.0, 0.0, 0.0, 0.0);
	//图像进行滤波
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			//计算采样点，得到当前像素附近的像素的坐标
			vec2 _xy_new = vec2(_xy.x + _filter_pos_delta[i][j].x,
								_xy.y + _filter_pos_delta[i][j].y);
			vec2 _uv_new = vec2(_xy_new.x / TexSize.x, _xy_new.y / TexSize.y);
			final_color += texture2D(_image, _uv_new) * _filter[i][j];
		}
	}
	return final_color;
}

void main()
{
	vec2 intXY = vec2(v_texCoord.x*TexSize.x, v_texCoord.y*TexSize.y);
	
	//BOX模糊
   //mat3		_pencil_fil = mat3 (1/9.0 ,1/9.0,1/9.0 ,
   //                             1/9.0 ,1/9.0,1/9.0 ,
   //                             1/9.0 ,1/9.0,1/9.0); 

   //高斯模糊
   //mat3		_pencil_fil = mat3 (1/16.0 ,1/8.0,1/16.0 ,
   //                             1/8.0 ,1/4.0,1/8.0 ,
   //
                                 1/16.0 ,1/8.0,1/16.0); 
	//锐化
	mat3 _pencil_fil = mat3(-1, -1, -1,
							-1, 9.0, -1,
							-1, -1, -1);

	gl_FragColor = dip_filter(_pencil_fil, CC_Texture0, intXY, TexSize);
}
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
        { vec2(-1.0 , -1.0) , vec2(0,-1.0), vec2(1.0 , -1.0) },
        { vec2( -1.0 , 0.0) , vec2(0, 0.0), vec2(1.0 ,  0.0) },
        { vec2( -1.0 , 1.0) , vec2(0, 1.0), vec2(1.0 ,  1.0) },
     };
     //最终的输出颜色
     vec4 final_color = vec4(0.0,0.0,0.0,0.0);
     //对图像做滤波操作
     for(int i = 0 ; i < 3 ; i ++ )
     {
         for(int j = 0 ; j < 3 ; j ++)
         {
            //计算采样点，得到当前像素附近的像素的坐标
              vec2 _xy_new = vec2(_xy.x + _filter_pos_delta[i][j].x ,_xy.y + _filter_pos_delta[i][j].y);           
			  vec2 _uv_new = vec2(_xy_new.x/texSize.x , _xy_new.y/texSize.y);
            //采样并乘以滤波器权重，然后累加
              final_color += texture2D( _image, _uv_new ) * _filter[i][j];
         } 
     }
     return final_color;
}

void main()
{
   vec2		intXY = vec2(v_texCoord.x * TexSize.x , v_texCoord.y * TexSize.y);
   //权重 只要保证最后的和是1就可以修改后的效果会有点不同但大至效果是一样的
   mat3		_pencil_fil = mat3 (-1.0 ,-1.0  , 1.0 ,
                                -2.0 ,  1.0 , 1.0 ,
                                -1.0  , 1.0 , 1.0 ); 
   vec4		delColor =  dip_filter(_pencil_fil , CC_Texture0 , intXY, TexSize);
   float	deltaGray = 0.3 * delColor.x  + 0.59 * delColor.y  + 0.11* delColor.z;    
                
   if(deltaGray < 0.0) deltaGray = -1.0 * deltaGray;
   deltaGray = 1.0 - deltaGray;
   gl_FragColor = vec4(deltaGray, deltaGray, deltaGray, 1.0);
}
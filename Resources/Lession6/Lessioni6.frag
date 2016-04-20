#ifdef GL_ES
varying mediump vec2 v_texCoord;
varying lowp vec4 v_color;
#else
varying vec2 v_texCoord;
varying vec4 v_color;
#endif

uniform vec2 u_TexUV;
uniform sampler2D u_texture;
void main()
{
	gl_FragColor = texture2D(CC_Texture0, v_texCoord+u_TexUV) * v_color * texture2D(u_texture, v_texCoord);;
}
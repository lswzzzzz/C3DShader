#ifndef _C3DPLANERENDER_H
#define _C3DPLANERENDER_H
#include "cocos2d.h"
#include <vector>
using namespace std;
USING_NS_CC;
//顶点通道类型
enum VertexChannelType
{
	VERTEX_ATTRIB_POSITION,
	VERTEX_ATTRIB_COLOR,
	VERTEX_ATTRIB_TEX_COORD,
	VERTEX_ATTRIB_TEX_COORD1,
	VERTEX_ATTRIB_TEX_COORD2,
	VERTEX_ATTRIB_TEX_COORD3,
	VERTEX_ATTRIB_NORMAL,
	VERTEX_ATTRIB_TANGENT,
	VERTEX_ATTRIB_BITANGENT,
	VERTEX_ATTRIB_BLEND_WEIGHT,
	VERTEX_ATTRIB_BLEND_INDEX,
	VERTEX_ATTRIB_MAX,

	// backward compatibility
	VERTEX_ATTRIB_TEX_COORDS = VERTEX_ATTRIB_TEX_COORD,
};

//索引类型
enum IndexFormat
{
	INDEX8 = GL_UNSIGNED_BYTE,
	INDEX16 = GL_UNSIGNED_SHORT,
};

//图形绘制类型
enum PrimitiveType
{
	PT_POINTS = GL_POINTS,
	PT_TRIANGLES = GL_TRIANGLES,
	PT_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	PT_LINES = GL_LINES,
	PT_LINE_STRIP = GL_LINE_STRIP
};

//结构
struct	stShapeBumpVertices
{
	Vec3 		Position;	//位置
	Vec3		Normal;	 	//法线
	Vec2		TexUV;		//贴图坐标
	Vec3		Tangent;	//切线
	Vec3		Bitangent;  //副切线
}
;
class C3DPlaneRender	:public Node
{
public:
	//构造
	C3DPlaneRender();
	//析构
	~C3DPlaneRender();
	//重载渲染
	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
public:
	//初始化
	void			Init(const Vec3& vPos);
	//清空
	void			CleanUp();
	//释放
	void			Release();
	//渲染
	void			Render();
	//使用贴图
	void			SetTexture(CCTexture2D*	pTexture, CCTexture2D* pBumpTexture);
	//创建Shader
	bool			BuildShader();
	//渲染-法线贴图模式
	void			Render_Bump();
protected:
	//图形渲染方式
	PrimitiveType				m_PrimitiveType;
	//索引格式
    IndexFormat					m_IndexFormat;
	//顶点数组
	stShapeBumpVertices*		m_BumpVertexArray;
	//索引数组
    GLushort*					m_IndiceArray;
	//VB
    GLuint						m_VertexBuffer;
	//IB
    GLuint						m_IndexBuffer;
	//顶点数量
	unsigned int				m_VertexCount;
	//索引数量
	unsigned int				m_IndexCount;
	//所用的Shader
	GLProgram*					m_ShaderProgram;
	//使用的贴图
	CCTexture2D*				m_Texture;
	//使用的法线贴图
	CCTexture2D*				m_BumpTexture;
	//混合方式
	BlendFunc					m_BlendFunc;
	//相应的位置
	Vec3						m_Pos;
}
;


#endif

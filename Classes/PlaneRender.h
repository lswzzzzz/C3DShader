#ifndef _C3DPLANERENDER_H
#define _C3DPLANERENDER_H
#include "cocos2d.h"
#include <vector>
using namespace std;
USING_NS_CC;
//����ͨ������
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

//��������
enum IndexFormat
{
	INDEX8 = GL_UNSIGNED_BYTE,
	INDEX16 = GL_UNSIGNED_SHORT,
};

//ͼ�λ�������
enum PrimitiveType
{
	PT_POINTS = GL_POINTS,
	PT_TRIANGLES = GL_TRIANGLES,
	PT_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	PT_LINES = GL_LINES,
	PT_LINE_STRIP = GL_LINE_STRIP
};

//�ṹ
struct	stShapeBumpVertices
{
	Vec3 		Position;	//λ��
	Vec3		Normal;	 	//����
	Vec2		TexUV;		//��ͼ����
	Vec3		Tangent;	//����
	Vec3		Bitangent;  //������
}
;
class C3DPlaneRender	:public Node
{
public:
	//����
	C3DPlaneRender();
	//����
	~C3DPlaneRender();
	//������Ⱦ
	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
public:
	//��ʼ��
	void			Init(const Vec3& vPos);
	//���
	void			CleanUp();
	//�ͷ�
	void			Release();
	//��Ⱦ
	void			Render();
	//ʹ����ͼ
	void			SetTexture(CCTexture2D*	pTexture, CCTexture2D* pBumpTexture);
	//����Shader
	bool			BuildShader();
	//��Ⱦ-������ͼģʽ
	void			Render_Bump();
protected:
	//ͼ����Ⱦ��ʽ
	PrimitiveType				m_PrimitiveType;
	//������ʽ
    IndexFormat					m_IndexFormat;
	//��������
	stShapeBumpVertices*		m_BumpVertexArray;
	//��������
    GLushort*					m_IndiceArray;
	//VB
    GLuint						m_VertexBuffer;
	//IB
    GLuint						m_IndexBuffer;
	//��������
	unsigned int				m_VertexCount;
	//��������
	unsigned int				m_IndexCount;
	//���õ�Shader
	GLProgram*					m_ShaderProgram;
	//ʹ�õ���ͼ
	CCTexture2D*				m_Texture;
	//ʹ�õķ�����ͼ
	CCTexture2D*				m_BumpTexture;
	//��Ϸ�ʽ
	BlendFunc					m_BlendFunc;
	//��Ӧ��λ��
	Vec3						m_Pos;
}
;


#endif

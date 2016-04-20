#include "PlaneRender.h"

//构造
C3DPlaneRender::C3DPlaneRender():
	m_VertexBuffer(0)
	,m_IndexBuffer(0)
	,m_PrimitiveType(PT_TRIANGLES)
	,m_IndexFormat(INDEX16)
	,m_BumpVertexArray(0)
	,m_IndiceArray(0)
	,m_VertexCount(0)
	,m_IndexCount(0)
	,m_ShaderProgram(NULL)
	,m_Texture(NULL)
	,m_BumpTexture(NULL)
{
	m_Pos = Vec3(0, 0, 0);
}
//析构
C3DPlaneRender::~C3DPlaneRender()
{

}
//重载渲染
void C3DPlaneRender::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	if (m_BumpTexture)
	{
		Render_Bump();
	}
}

//初始化
void	C3DPlaneRender::Init(const Vec3& vPos)
{
	m_Pos = vPos;
	glGenBuffers(1, &m_VertexBuffer);
	glGenBuffers(1, &m_IndexBuffer);
	m_VertexCount = 4 ;
	m_IndexCount = 6 ;
	m_PrimitiveType = PT_TRIANGLES;
	m_IndiceArray = new GLushort[m_IndexCount];

	m_IndiceArray[0] = 0;
	m_IndiceArray[1] = 1;
	m_IndiceArray[2] = 2;

	m_IndiceArray[3] = 0;
	m_IndiceArray[4] = 2;
	m_IndiceArray[5] = 3;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexCount*sizeof(GLushort), m_IndiceArray, GL_STATIC_DRAW);


	m_BumpVertexArray = new stShapeBumpVertices[m_VertexCount];

	//近
	m_BumpVertexArray[0].Position = m_Pos + Vec3(0, 0, 0);
	m_BumpVertexArray[0].Normal = Vec3(0, 0, -1);
	//这个是UI坐标系
	m_BumpVertexArray[0].TexUV = Vec2(0, 1);
	m_BumpVertexArray[1].Position = m_Pos + Vec3(0, 1, 0);
	m_BumpVertexArray[1].Normal = Vec3(0, 0, -1);
	m_BumpVertexArray[1].TexUV = Vec2(0, 0);
	m_BumpVertexArray[2].Position = m_Pos + Vec3(1, 1, 0);
	m_BumpVertexArray[2].Normal = Vec3(0, 0, -1);
	m_BumpVertexArray[2].TexUV = Vec2(1, 0);
	m_BumpVertexArray[3].Position = m_Pos + Vec3(1, 0, 0);
	m_BumpVertexArray[3].Normal = Vec3(0, 0, -1);
	m_BumpVertexArray[3].TexUV = Vec2(1, 1);

	for (int i = 0; i < m_IndexCount; i += 3)
	{
		int     i0 = m_IndiceArray[i];
		int		i1 = m_IndiceArray[i + 1];
		int		i2 = m_IndiceArray[i + 2];

		Vec3&	v0 = m_BumpVertexArray[i0].Position;
		Vec3&	v1 = m_BumpVertexArray[i1].Position;
		Vec3&	v2 = m_BumpVertexArray[i2].Position;

		Vec2&	uv0 = m_BumpVertexArray[i0].TexUV;
		Vec2&	uv1 = m_BumpVertexArray[i1].TexUV;
		Vec2&	uv2 = m_BumpVertexArray[i2].TexUV;

		Vec3	deltaPos1 = v1 - v0;
		Vec3    deltaPos2 = v2 - v0;

		Vec2    deltaUV1 = uv1 - uv0;
		Vec2    deltaUV2 = uv2 - uv0;

		float   r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);

		Vec3    tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
		Vec3    bitgent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

		m_BumpVertexArray[i0].Tangent = tangent;
		m_BumpVertexArray[i1].Tangent = tangent;
		m_BumpVertexArray[i2].Tangent = tangent;

		m_BumpVertexArray[i0].Bitangent = bitgent;
		m_BumpVertexArray[i1].Bitangent = bitgent;
		m_BumpVertexArray[i2].Bitangent = bitgent;
	}

	//释放VB
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_VertexCount*sizeof(stShapeBumpVertices), m_BumpVertexArray, GL_STATIC_DRAW);
}

//释放
void	C3DPlaneRender::Release()
{
	//释放VB数组
	if (m_BumpVertexArray)
	{
		delete[] m_BumpVertexArray;
		m_BumpVertexArray = NULL;
	}
	//释放索引数组
	if (m_IndiceArray)
	{
		delete[] m_IndiceArray;
		m_IndiceArray = NULL;
	}
	m_VertexCount = 0;
	m_IndexCount = 0;
	//释放VB
	if (glIsBuffer(m_VertexBuffer))
	{
		glDeleteBuffers(1, &m_VertexBuffer);
		m_VertexBuffer = 0;
	}
	//释放IB
	if (glIsBuffer(m_IndexBuffer))
	{
		glDeleteBuffers(1, &m_IndexBuffer);
		m_IndexBuffer = 0;
	}
}

//使用贴图
void    C3DPlaneRender::SetTexture(CCTexture2D*	pTexture,CCTexture2D* pBumpTexture)
{
	m_Texture = pTexture ;
	m_BumpTexture = pBumpTexture;
}	

//创建Shader
bool	C3DPlaneRender::BuildShader()
{
	m_ShaderProgram = new GLProgram();
	if (!m_ShaderProgram)
		return NULL;
	if (true == m_ShaderProgram->initWithFilenames("Lession28.vert", "Lession28.frag"))
	{
		m_ShaderProgram->bindAttribLocation("a_position", VERTEX_ATTRIB_POSITION);
		m_ShaderProgram->bindAttribLocation("a_texCoord", VERTEX_ATTRIB_TEX_COORD);
		m_ShaderProgram->bindAttribLocation("a_normal", VERTEX_ATTRIB_NORMAL);
		m_ShaderProgram->bindAttribLocation("a_tangent", VERTEX_ATTRIB_TANGENT);
		m_ShaderProgram->bindAttribLocation("a_bitangent", VERTEX_ATTRIB_BITANGENT);
		m_ShaderProgram->link();
		m_ShaderProgram->updateUniforms();
		m_ShaderProgram->retain();
		return true;
	}

	delete m_ShaderProgram;
	m_ShaderProgram = NULL;
	return false;
}	
//渲染-法线贴图模式
void	C3DPlaneRender::Render_Bump()
{
#define kShapeBumpVertexStructSize sizeof(stShapeBumpVertices)

	if (m_ShaderProgram && m_VertexCount > 0 && m_IndexCount > 0 && m_IndiceArray)
	{
		//开启Shader的使用
		m_ShaderProgram->use();
		//更新Cocos2d-x中为Shader预定义的变量
		m_ShaderProgram->setUniformsForBuiltins();

		//设置色彩
		ccColor4F s_tColor = ccc4f(1.0f, 1.0f, 1.0f, 1.0f);
		GLuint	  uColorId = m_ShaderProgram->getUniformLocationForName("MeshVertexColor");
		m_ShaderProgram->setUniformLocationWith4fv(uColorId, (GLfloat*)&s_tColor.r, 1);

		//光照方向
		Vec3	  tLightDir(-1, -1, 0);
		GLuint nLightDirId = m_ShaderProgram->getUniformLocationForName("LightDir");
		m_ShaderProgram->setUniformLocationWith3fv(nLightDirId, (GLfloat*)&tLightDir, 1);

		//眼睛观察的方向
		Vec3	  tViewDir = Vec3(0, 0,-1);
		GLuint	  uViewDirId = m_ShaderProgram->getUniformLocationForName("ViewDir");
		m_ShaderProgram->setUniformLocationWith3fv(uViewDirId, (GLfloat*)&tViewDir.x, 1);

		//眼睛观察的方向
		Vec3	  tEyePos = Vec3(0, 0, 1);
		GLuint	  uEyePosId = m_ShaderProgram->getUniformLocationForName("EyePos");
		m_ShaderProgram->setUniformLocationWith3fv(uEyePosId, (GLfloat*)&tEyePos.x, 1);

		float	f_SpecularPower = 8.5;
		GLuint nFloatParamIndex = m_ShaderProgram->getUniformLocationForName("SpecularPower");
		m_ShaderProgram->setUniformLocationWith1f(nFloatParamIndex, f_SpecularPower);
		
		float	f_SpecularLevel = 1.0;
		nFloatParamIndex = m_ShaderProgram->getUniformLocationForName("SpecularLevel");
		m_ShaderProgram->setUniformLocationWith1f(nFloatParamIndex, f_SpecularLevel);
		//普通贴图
		if (m_Texture)
		{
			GLuint nTextureId = m_ShaderProgram->getUniformLocationForName("CC_Texture0");
			m_ShaderProgram->setUniformLocationWith1i(nTextureId, 0);
			GL::bindTexture2DN(0, m_Texture->getName());
		}
		//法线贴图
		if (m_BumpTexture)
		{
			GLuint nTextureId = m_ShaderProgram->getUniformLocationForName("CC_Texture_Bump");
			m_ShaderProgram->setUniformLocationWith1i(nTextureId, 1);
			GL::bindTexture2DN(1, m_BumpTexture->getName());
		}
	
		//旋转
		kmMat4 matrixP;
		kmMat4 matrixMV;
		kmMat4 matrixMVP;
		kmMat4 matrixWorld;
		kmMat4 matrixMVPW;

		kmGLGetMatrix(KM_GL_PROJECTION, &matrixP);
		kmGLGetMatrix(KM_GL_MODELVIEW, &matrixMV);
		kmMat4Multiply(&matrixMVP, &matrixP, &matrixMV);

		//取得结点的世界矩阵
		matrixWorld = Mat4::IDENTITY;
		GLuint matrixId = m_ShaderProgram->getUniformLocationForName("matRotate");
		m_ShaderProgram->setUniformLocationWithMatrix4fv(matrixId, matrixMV.m, 1);

		auto mvmatrixId = m_ShaderProgram->getUniformLocationForName("CC_MVMatrix");
		m_ShaderProgram->setUniformLocationWithMatrix4fv(mvmatrixId, matrixMV.m, 1);

		matrixId = m_ShaderProgram->getUniformLocationForName("CC_MVPMatrix");
		kmMat4Multiply(&matrixMVPW, &matrixMVP, &matrixWorld);
		m_ShaderProgram->setUniformLocationWithMatrix4fv(matrixId, matrixMVPW.m, 1);

		//绑定VB
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		//glEnableClientState(GL_VERTEX_ARRAY);

		// vertices
		glEnableVertexAttribArray(VERTEX_ATTRIB_POSITION);
		glVertexAttribPointer(VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kShapeBumpVertexStructSize, (GLvoid*)offsetof(stShapeBumpVertices, Position));
		// normal
		glEnableVertexAttribArray(VERTEX_ATTRIB_NORMAL);
		glVertexAttribPointer(VERTEX_ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, kShapeBumpVertexStructSize, (GLvoid*)offsetof(stShapeBumpVertices, Normal));
		// tex coords
		glEnableVertexAttribArray(VERTEX_ATTRIB_TEX_COORD);
		glVertexAttribPointer(VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, kShapeBumpVertexStructSize, (GLvoid*)offsetof(stShapeBumpVertices, TexUV));
		// tangent
		glEnableVertexAttribArray(VERTEX_ATTRIB_TANGENT);
		glVertexAttribPointer(VERTEX_ATTRIB_TANGENT, 3, GL_FLOAT, GL_FALSE, kShapeBumpVertexStructSize, (GLvoid*)offsetof(stShapeBumpVertices, Tangent));
		// bitangent
		glEnableVertexAttribArray(VERTEX_ATTRIB_BITANGENT);
		glVertexAttribPointer(VERTEX_ATTRIB_BITANGENT, 3, GL_FLOAT, GL_FALSE, kShapeBumpVertexStructSize, (GLvoid*)offsetof(stShapeBumpVertices, Bitangent));


		//绑定IB
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		//glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);
		//使用IB进行绘制
		glDrawElements(m_PrimitiveType, (GLsizei)m_IndexCount, m_IndexFormat, 0);


		//取消绑定
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//绘制数加一
		CC_INCREMENT_GL_DRAWS(1);
	}

}

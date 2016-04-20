#include "Lession6.h"

USING_NS_CC;

Scene* Lession6::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Lession6::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Lession6::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto size = Director::getInstance()->getWinSize();
	FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getSearchPaths().at(0) + "Lession6/");

	auto sprite = Sprite::create("Logo.png");
	sprite->setPosition(size.width / 2, size.height / 2);
	//sprite->setColor(Color3B(0, 0, 255));
	addChild(sprite);
	m_sprite = sprite;

	Texture2D::TexParams texParams;
	texParams.minFilter = GL_NEAREST;
	texParams.magFilter = GL_NEAREST;
	texParams.wrapS = GL_REPEAT;
	texParams.wrapT = GL_REPEAT;
	sprite->getTexture()->setTexParameters(texParams);

	m_TexUVAni.x = m_TexUVAni.y = 0.0;
	auto shader = GLProgram::createWithFilenames("Lessioni6.vert", "Lessioni6.frag");
	auto state = GLProgramState::create(shader);
	auto texture = TextureCache::getInstance()->addImage("Texture2.jpg");
	state->setUniformTexture("u_texture", texture);
	state->applyUniforms();
	sprite->setGLProgramState(state);
	
	
	schedule(schedule_selector(Lession6::UpdateTexUVAni, this));

    return true;
}

void Lession6::UpdateTexUVAni(float dt)
{
	m_TexUVAni.x += dt;
	m_sprite->getGLProgramState()->setUniformVec2("u_TexUV", m_TexUVAni);
}
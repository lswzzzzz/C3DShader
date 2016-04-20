#include "Lession5.h"

USING_NS_CC;

Scene* Lession5::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Lession5::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Lession5::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto size = Director::getInstance()->getWinSize();
	FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getSearchPaths().at(0) + "Lession5/");

	auto sprite = Sprite::create("Logo.png");
	sprite->setPosition(size.width / 2, size.height / 2);
	sprite->setColor(Color3B(0, 0, 255));
	addChild(sprite);
	m_sprite = sprite;

	Texture2D::TexParams texParams;
	texParams.minFilter = GL_NEAREST;
	texParams.magFilter = GL_NEAREST;
	texParams.wrapS = GL_REPEAT;
	texParams.wrapT = GL_REPEAT;
	sprite->getTexture()->setTexParameters(texParams);

	m_TexUVAni.x = m_TexUVAni.y = 0.0;
	auto shader = GLProgram::createWithFilenames("Lessioni5.vert", "Lessioni5.frag");
	auto state = GLProgramState::create(shader);
	state->applyUniforms();
	sprite->setGLProgramState(state);

	schedule(schedule_selector(Lession5::UpdateTexUVAni, this));

    return true;
}

void Lession5::UpdateTexUVAni(float dt)
{
	m_TexUVAni.x += dt;
	m_sprite->getGLProgramState()->setUniformVec2("u_TexUV", m_TexUVAni);
}
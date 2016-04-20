#include "Lession12.h"

USING_NS_CC;

Scene* Lession12::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Lession12::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Lession12::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto winSize = Director::getInstance()->getWinSize();
	FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getSearchPaths().at(0) + "Lession12/");

	auto sprite = Sprite::create("Logo.png");
	sprite->setPosition(winSize.width / 2, winSize.height / 2);
	addChild(sprite);
	m_sprite = sprite;

	auto shader = GLProgram::createWithFilenames("Lession12.vert", "Lession12.frag");
	auto state = GLProgramState::create(shader);
	auto size = sprite->getContentSize();
	state->setUniformVec2("TexSize", Vec2(size));
	state->applyUniforms();
	sprite->setGLProgramState(state);

    return true;
}

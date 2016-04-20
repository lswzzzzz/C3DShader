#include "Lession10.h"

USING_NS_CC;

Scene* Lession10::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Lession10::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Lession10::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto winSize = Director::getInstance()->getWinSize();
	FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getSearchPaths().at(0) + "Lession10/");

	auto sprite = Sprite::create("Logo.png");
	sprite->setPosition(winSize.width / 2, winSize.height / 2);
	addChild(sprite);
	m_sprite = sprite;

	auto shader = GLProgram::createWithFilenames("Lession10.vert", "Lession10.frag");
	auto state = GLProgramState::create(shader);
	auto size = sprite->getContentSize();
	state->setUniformVec2("TexSize", Vec2(size));
	state->applyUniforms();
	sprite->setGLProgramState(state);

    return true;
}

#include "Lession9.h"

USING_NS_CC;

Scene* Lession9::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Lession9::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Lession9::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto winSize = Director::getInstance()->getWinSize();
	FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getSearchPaths().at(0) + "Lession9/");

	auto sprite = Sprite::create("Logo.png");
	sprite->setPosition(winSize.width / 2, winSize.height / 2);
	addChild(sprite);
	m_sprite = sprite;

	auto shader = GLProgram::createWithFilenames("Lession9.vert", "Lession9.frag");
	auto state = GLProgramState::create(shader);
	auto size = sprite->getContentSize();
	state->setUniformVec2("TexSize", Vec2(size));
	float PI = 3.1415926535898;
	float sigma = 1.5;
	state->setUniformFloat("PI", PI);
	state->setUniformFloat("sigma2", sigma * sigma * 2);
	state->applyUniforms();
	sprite->setGLProgramState(state);
    return true;

}

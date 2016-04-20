#include "Lession8.h"

USING_NS_CC;

Scene* Lession8::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Lession8::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Lession8::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto winSize = Director::getInstance()->getWinSize();
	FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getSearchPaths().at(0) + "Lession8/");

	auto sprite = Sprite::create("Logo.png");
	sprite->setPosition(winSize.width / 2, winSize.height / 2);
	addChild(sprite);
	m_sprite = sprite;

	m_time = 0.0f;
	auto shader = GLProgram::createWithFilenames("Lessioni8.vert", "Lessioni8.frag");
	auto state = GLProgramState::create(shader);
	auto size = sprite->getContentSize();
	state->setUniformVec2("TexSize", Vec2(size));
	bool openChangeSize = false;
	if (!openChangeSize){
		blockSize = 6.0f;
		state->setUniformVec2("mosaicSize", Vec2(blockSize, blockSize));
	}

	state->applyUniforms();
	sprite->setGLProgramState(state);
	if (openChangeSize){
		schedule(schedule_selector(Lession8::UpdateMSK, this));
	}
	else{
		schedule(schedule_selector(Lession8::UpdateMSK2, this));
	}
    return true;
}


void Lession8::UpdateMSK(float dt)
{
	m_time += dt;
	float fMSKSize = (sin(m_time) + 2.0) * 8;
	m_sprite->getGLProgramState()->setUniformInt("open", 0);
	m_sprite->getGLProgramState()->setUniformVec2("mosaicSize", Vec2(fMSKSize, fMSKSize));
}

void Lession8::UpdateMSK2(float dt)
{
	m_time += dt;
	float index = sin(m_time*1.5) + 1.0;
	m_sprite->getGLProgramState()->setUniformInt("open", 1);
	m_sprite->getGLProgramState()->setUniformFloat("index", index);
}
#include "Lession13.h"

USING_NS_CC;

Scene* Lession13::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Lession13::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Lession13::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto winSize = Director::getInstance()->getWinSize();
	FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getSearchPaths().at(0) + "Lession13/");

	auto sprite = Sprite::create("Logo.png");
	sprite->setPosition(winSize.width / 2, winSize.height / 2);
	addChild(sprite);
	m_sprite = sprite;

	auto shader = GLProgram::createWithFilenames("Lession13.vert", "Lession13.frag");
	auto state = GLProgramState::create(shader);
	state->applyUniforms();
	sprite->setGLProgramState(state);

	for (int i = 0; i < 2; i++){
		m_LightRange[i] = 50;
	}
	m_LightPos[0] = Vec2(winSize.width*0.45, winSize.height*0.5);
	m_LightPos[1] = Vec2(winSize.width*0.55, winSize.height*0.5);
	m_LightColor[0] = Vec4(1.0, 1.0, 0.0, 1.0);
	m_LightColor[1] = Vec4(0.0, 1.0, 1.0, 1.0);
	m_fTime = 0.0;
	//创建一个定时器，实现点光源的更新
	schedule(schedule_selector(Lession13::UpdateLight));

    return true;
}

void Lession13::UpdateLight(float dt)
{
	m_fTime += dt;
	auto s = Director::getInstance()->getWinSize();
	m_LightPos[0] = Vec2(s.width*0.45, s.height*0.5) + Vec2(sinf(m_fTime) * 50, cosf(m_fTime) * 50);
	m_LightPos[1] = Vec2(s.height*0.55, s.height*0.5) + Vec2(sinf(m_fTime) * 50, cosf(m_fTime) * 50);
	m_sprite->getGLProgramState()->setUniformVec2v("LightPos", 2, m_LightPos);
	m_sprite->getGLProgramState()->setUniformFloatv("LightRange", 2, m_LightRange);
	m_sprite->getGLProgramState()->setUniformVec4v("LightColor", 2, m_LightColor);
}
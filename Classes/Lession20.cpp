#include "Lession20.h"

USING_NS_CC;

Scene* Lession20::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Lession20::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Lession20::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto winSize = Director::getInstance()->getWinSize();
	FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getSearchPaths().at(0) + "Lession20/");

	////得到屏幕尺寸
	auto s = Director::getInstance()->getWinSize();
	//创建3D摄像机
	auto _camera = cocos2d::Camera::createPerspective(60, (GLfloat)s.width / s.height, 1, 1000);
	//设置摄像机眼睛位置
	_camera->setPosition3D(Vec3(0, 50, 50));
	//设置摄像机观察点位置
	_camera->lookAt(Vec3(0, 0, 0));
	_camera->setCameraFlag(CameraFlag::USER1);
	addChild(_camera);

	//创建静态模型
	auto spriteStatic3D = Sprite3D::create("mod_niutou.c3b");
	_sprite3D = spriteStatic3D;
	spriteStatic3D->setCameraMask(2);
	spriteStatic3D->setScale(0.1);
	spriteStatic3D->setPosition3D(Vec3(0, 0, 0));
	spriteStatic3D->setRotation3D(Vec3(-90, 0, 0));
	spriteStatic3D->getMeshByIndex(1)->setVisible(false);
	addChild(spriteStatic3D);

	Texture2D* pMaskTexture = Director::getInstance()->getTextureCache()->addImage("mod_m_niutou01_mask.jpg");

	//创建Shader
	_pProgramState = GLProgramState::create(GLProgram::createWithFilenames("Lession20.vert", "Lession20.frag"));
	_pProgramState->setUniformTexture("u_MaskTexture", pMaskTexture);
	_pProgramState->applyUniforms();
	spriteStatic3D->setGLProgramState(_pProgramState);

	m_fTime = 0.0;
	schedule(schedule_selector(Lession20::UpdateEyeColor));

    return true;
}

//更新眼睛色彩的函数
void Lession20::UpdateEyeColor(float dt)
{
	m_fTime += dt;
	Vec4 _EyeColor = Vec4((cosf(m_fTime) + 1.0) * 0.5, 0.0, (sinf(m_fTime) + 1.0) * 0.5, 1.0);
	_pProgramState->setUniformVec4("u_EyeColor", _EyeColor);
}
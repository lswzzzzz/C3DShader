#include "Lession21.h"

USING_NS_CC;

Scene* Lession21::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Lession21::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Lession21::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto winSize = Director::getInstance()->getWinSize();
	FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getSearchPaths().at(0) + "Lession21/");

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

	auto spriteStatic3D = Sprite3D::create("qiu.c3b");
	_sprite3D = spriteStatic3D;
	spriteStatic3D->setCameraMask(2);
	spriteStatic3D->setScale(0.5);
	spriteStatic3D->setPosition3D(Vec3(0, -20, 0));
	spriteStatic3D->setRotation3D(Vec3(0, 0, 0));
	addChild(spriteStatic3D);
	
	_pProgramState = GLProgramState::create(GLProgram::createWithFilenames("Lession21.vert", "Lession21.frag"));
	_LightDir = Vec3(-1.0, 0.0, 0.0);
	_pProgramState->setUniformVec3("u_LightDir", _LightDir);
	_pProgramState->applyUniforms();
	//模型应用Shader
	spriteStatic3D->setGLProgramState(_pProgramState);
	_RotateY = 0.0;
	schedule(schedule_selector(Lession21::RotateQiu));

    return true;
}

// 定时刷新函数
void	Lession21::RotateQiu(float dt)
{
	_RotateY += dt * 10;
	_sprite3D->setRotation3D(Vec3(0, _RotateY, 0));
}
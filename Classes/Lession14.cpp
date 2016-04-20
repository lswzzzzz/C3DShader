#include "Lession14.h"

USING_NS_CC;

Scene* Lession14::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Lession14::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Lession14::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto winSize = Director::getInstance()->getWinSize();
	FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getSearchPaths().at(0) + "Lession14/");

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
	auto spriteStatic3D = Sprite3D::create("qiu.c3t");
	_sprite3D = spriteStatic3D;
	spriteStatic3D->setCameraMask(2);
	spriteStatic3D->setScale(0.5);
	spriteStatic3D->setPosition3D(Vec3(0, 0, 0));
	spriteStatic3D->setRotation3D(Vec3(0, 0, 0));
	//设置不使用灯光标记
	spriteStatic3D->setLightMask(0);
	addChild(spriteStatic3D);

	//创建Shader
	GLProgramState*	_pProgramState = GLProgramState::create(GLProgram::createWithFilenames("Lession14.vert", "Lession14.frag"));
	_pProgramState->setUniformVec4("u_color", Vec4(1.0, 0.0, 1.0, 1.0));
	_pProgramState->applyUniforms();
	spriteStatic3D->setGLProgramState(_pProgramState);

    return true;
}
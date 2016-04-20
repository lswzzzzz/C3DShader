#include "Lession24.h"

USING_NS_CC;

Scene* Lession24::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Lession24::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Lession24::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto winSize = Director::getInstance()->getWinSize();
	FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getSearchPaths().at(0) + "Lession24/");

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
	auto spriteStatic3D = Sprite3D::create("plane.c3t");
	spriteStatic3D->setCameraMask(2);
	spriteStatic3D->setPosition3D(Vec3(0, -50, 0));
	spriteStatic3D->setRotation3D(Vec3(-90, 0, 0));
	addChild(spriteStatic3D);

	//创建静态模型
	spriteStatic3D = Sprite3D::create("qiu.c3t");
	_sprite3D = spriteStatic3D;
	spriteStatic3D->setCameraMask(2);
	spriteStatic3D->setScale(0.5);
	spriteStatic3D->setPosition3D(Vec3(0, -20, 0));
	spriteStatic3D->setRotation3D(Vec3(0, 0, 0));
	addChild(spriteStatic3D);

	//spriteStatic3D->setBlendFunc(BlendFunc::ALPHA_NON_PREMULTIPLIED);
	Texture2D* texture = TextureCache::getInstance()->addImage("alpha.jpg");

	GLProgramState* state = GLProgramState::create(GLProgram::createWithFilenames("Lession24.vert", "Lession24.frag"));
	state->setUniformTexture("u_Texture", texture);
	state->applyUniforms();
	spriteStatic3D->setGLProgramState(state);

    return true;

}

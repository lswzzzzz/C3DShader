#include "Lession23.h"

USING_NS_CC;

Scene* Lession23::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Lession23::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Lession23::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto winSize = Director::getInstance()->getWinSize();
	FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getSearchPaths().at(0) + "Lession23/");

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
	addChild(spriteStatic3D);


	//创建Shader
	_pProgramState = GLProgramState::create(GLProgram::createWithFilenames("Lession23.vert", "Lession23.frag"));
	_PointLightPositionArray[0] = Vec3(50.0, 0.0, 0.0);
	_PointLightPositionArray[1] = Vec3(0, 50.0, 0);
	_PointLightPositionArray[2] = Vec3(-50.0, 0, 0);
	_PointLightRangeArray[0] = 100;
	_PointLightRangeArray[1] = 100;
	_PointLightRangeArray[2] = 100;
	_PointLightColorArray[0] = Vec3(1.0, 0, 0);
	_PointLightColorArray[1] = Vec3(0, 1.0, 0);
	_PointLightColorArray[2] = Vec3(0, 0, 1.0);
	_pProgramState->setUniformVec3v("u_PointLightPositionArray", 3, _PointLightPositionArray);
	_pProgramState->setUniformFloatv("u_PointLightRange", 3, _PointLightRangeArray);
	_pProgramState->setUniformVec3v("u_PointLightColorArray", 3, _PointLightColorArray);
	Mat4 tMatrix = spriteStatic3D->getNodeToWorldTransform();
	_pProgramState->setUniformMat4("u_WorldMatrix", tMatrix);
	_pProgramState->applyUniforms();
	//模型应用Shader
	spriteStatic3D->setGLProgramState(_pProgramState);
	_RotateY = 0.0;
	schedule(schedule_selector(Lession23::RotateQiu));

    return true;

}

// 定时刷新函数
void Lession23::RotateQiu(float dt)
{
	_RotateY += dt * 10;
	_sprite3D->setRotation3D(Vec3(0, _RotateY, 0));
	Mat4 tMatrix = _sprite3D->getNodeToWorldTransform();
	_pProgramState->setUniformMat4("u_WorldMatrix", tMatrix);
}
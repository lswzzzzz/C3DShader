#include "Lession26.h"

USING_NS_CC;

Scene* Lession26::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Lession26::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Lession26::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto winSize = Director::getInstance()->getWinSize();
	FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getSearchPaths().at(0) + "Lession26/");

	////得到屏幕尺寸
	auto s = Director::getInstance()->getWinSize();
	//创建3D摄像机
	auto _camera = cocos2d::Camera::createPerspective(60, (GLfloat)s.width / s.height, 1, 1000);
	//设置摄像机眼睛位置
	_camera->setPosition3D(Vec3(0, 200, 400));
	//设置摄像机观察点位置
	_camera->lookAt(Vec3(0, 30, 0));
	_camera->setCameraFlag(CameraFlag::USER1);
	addChild(_camera);

	//创建一个模型面板
	auto _plane = Sprite3D::create("plane.c3t");
	_plane->setRotation3D(Vec3(90, 0, 0));
	_plane->setScale(10);
	_plane->setCameraMask(2);
	addChild(_plane);
	auto _pProgramState = GLProgramState::create(GLProgram::createWithFilenames("Lession26.vert", "Lession26.frag"));
	_pProgramState->setUniformVec4("u_fogColor", Vec4(0.5, 0.0, 0.0, 1.0));
	_pProgramState->setUniformFloat("u_fogStart", 100.0);
	_pProgramState->setUniformFloat("u_fogEnd", 500.0);
	_pProgramState->setUniformInt("u_fogEquation", 0);
	_pProgramState->applyUniforms();
	_plane->setGLProgramState(_pProgramState);

	//创建树
	createTrees();

    return true;

}

void Lession26::createTrees()
{	
	//创建静态模型
	for (int i = 0; i < 60; i++)
	{
		auto sprite3D = Sprite3D::create("tree.c3t");
		sprite3D->setScale(rand_0_1()*0.05 + 0.05);
		Vec3 tPosition = Vec3(rand_0_1() * 100 - 50, 0, rand_0_1() * 120 - 100);
		tPosition *= 10;
		sprite3D->setPosition3D(tPosition);
		sprite3D->setCameraMask(2);
		sprite3D->setRotation3D(Vec3(-90, 0, 0));
		//创建Shader
		GLProgramState*	_pProgramState = GLProgramState::create(GLProgram::createWithFilenames("tree_swing.vert", "Lession26.frag"));
		_pProgramState->setUniformFloat("uSwingRange", 10.0);
		_pProgramState->setUniformVec4("u_fogColor", Vec4(0.5, 0.0, 0.0, 1.0));
		_pProgramState->setUniformFloat("u_fogStart", 100.0);
		_pProgramState->setUniformFloat("u_fogEnd", 500.0);
		_pProgramState->setUniformInt("u_fogEquation", 0);
		_pProgramState->applyUniforms();
		//获取模型树叶子模型
		if (sprite3D->getMeshByIndex(0))
		{
			//树叶子模型应用摇摆效果
			sprite3D->getMeshByIndex(0)->setGLProgramState(_pProgramState);
		}
		//创建Shader
		_pProgramState = GLProgramState::create(GLProgram::createWithFilenames("Lession26.vert", "Lession26.frag"));
		_pProgramState->setUniformVec4("u_fogColor", Vec4(0.5, 0.0, 0.0, 1.0));
		_pProgramState->setUniformFloat("u_fogStart", 100.0);
		_pProgramState->setUniformFloat("u_fogEnd", 500.0);
		_pProgramState->setUniformInt("u_fogEquation", 0);
		_pProgramState->applyUniforms();
		//获取模型树叶子模型
		if (sprite3D->getMeshByIndex(1))
		{
			//树叶子模型应用摇摆效果
			sprite3D->getMeshByIndex(1)->setGLProgramState(_pProgramState);
		}
		addChild(sprite3D);
	}
}
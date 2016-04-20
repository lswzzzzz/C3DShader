#include "Lession29.h"

USING_NS_CC;

Scene* Lession29::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Lession29::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Lession29::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto winSize = Director::getInstance()->getWinSize();
	FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getSearchPaths().at(0) + "Lession29/");

	//得到屏幕尺寸
	auto s = Director::getInstance()->getWinSize();
	//创建3D层
	auto layer3D = Layer::create();
	addChild(layer3D, 0);

	//创建3D摄像机
	_camera = Camera::createPerspective(60, (GLfloat)s.width / s.height, 1, 1000);
	//设置摄像机眼睛位置
	_camera->setPosition3D(Vec3(0, 100, 100));
	//设置摄像机观察点位置
	_camera->lookAt(Vec3(0, 0, 0));
	_camera->setCameraFlag(CameraFlag::USER1);
	layer3D->addChild(_camera);
	layer3D->setCameraMask(2);
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(Lession29::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(Lession29::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(Lession29::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	////创建动画模型
	auto spriteAniMesh = Sprite3D::create("orc.c3b");
	_spriteAni3D = spriteAniMesh;
	spriteAniMesh->setCameraMask(2);
	spriteAniMesh->setScale(2);
	spriteAniMesh->setPosition3D(Vec3(0, 0, 0));
	spriteAniMesh->setRotation3D(Vec3(0, 180, 0));
	//创建3D模型动画
	auto animation = Animation3D::create("orc.c3b");
	if (animation)
	{
		auto animate = Animate3D::create(animation);
		spriteAniMesh->runAction(RepeatForever::create(animate));
	}

	////创建材质
	//auto aniMeshmMat = Material::createWithFilename("3d_AniMesh.material");
	//aniMeshmMat->setTechnique("normal");
	////设置材质
	//spriteAniMesh->setMaterial(aniMeshmMat);
	layer3D->addChild(spriteAniMesh);

    return true;

}

void Lession29::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{

}

void Lession29::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
	if (touches.size())
	{
		auto touch = touches[0];
		auto delta = touch->getDelta();

		_angle -= CC_DEGREES_TO_RADIANS(delta.x);
		if (_camera)
		{
			_camera->setPosition3D(Vec3(100 * sinf(_angle), 100.0f, 100 * cosf(_angle)));
			_camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
		}
	}
}

void Lession29::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{

}

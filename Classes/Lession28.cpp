#include "Lession28.h"
#include "PlaneRender.h"

USING_NS_CC;

Scene* Lession28::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Lession28::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Lession28::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto winSize = Director::getInstance()->getWinSize();
	FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getSearchPaths().at(0) + "Lession28/");

	//得到屏幕尺寸
	auto s = Director::getInstance()->getWinSize();
	//创建3D层
	auto layer3D = Layer::create();
	addChild(layer3D, 0);

	//创建3D摄像机
	_camera = Camera::createPerspective(60, (GLfloat)s.width / s.height, 0.1, 10);
	//设置摄像机眼睛位置
	_camera->setPosition3D(Vec3(0, 0, 1));
	//设置摄像机观察点位置
	_camera->lookAt(Vec3(0, 0, 0));
	_camera->setCameraFlag(CameraFlag::USER1);
	layer3D->addChild(_camera);
	layer3D->setCameraMask(2);

	auto sprite3D = new C3DPlaneRender();
	_sprite3D = sprite3D;
	sprite3D->Init(Vec3(-0.5, -0.5, 0));
	sprite3D->setCameraMask(2);
	sprite3D->BuildShader();
	//创建第二张纹理
	Texture2D*	pNewTexture1 = Director::getInstance()->getTextureCache()->addImage("Diffuse.jpg");
	//创建第二张纹理
	Texture2D*	pNewTexture2 = Director::getInstance()->getTextureCache()->addImage("Bump.jpg");
	sprite3D->SetTexture(pNewTexture1, pNewTexture2);

	layer3D->addChild(sprite3D);

	//添加触摸监听事件
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(Lession28::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(Lession28::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(Lession28::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;

}

void Lession28::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{

}

void Lession28::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
	if (touches.size())
	{
		auto touch = touches[0];
		auto delta = touch->getDelta();
		static  float angle = 0;
		angle -= CC_DEGREES_TO_RADIANS(delta.x);
		if (_camera)
		{
			_camera->setPosition3D(Vec3(1 * sinf(angle), 0.0f, 1 * cosf(angle)));
			_camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
		}
	}
}

void Lession28::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{

}

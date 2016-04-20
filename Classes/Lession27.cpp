#include "Lession27.h"

USING_NS_CC;

Scene* Lession27::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Lession27::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Lession27::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto winSize = Director::getInstance()->getWinSize();
	FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getSearchPaths().at(0) + "Lession27/");

	//得到屏幕尺寸
	auto s = Director::getInstance()->getWinSize();
	//创建3D层
	auto layer3D = Layer::create();
	addChild(layer3D, 0);

	//创建3D摄像机
	_camera = Camera::createPerspective(60, (GLfloat)s.width / s.height, 1, 1000);
	//设置摄像机眼睛位置
	_camera->setPosition3D(Vec3(0, 0, 50));
	//设置摄像机观察点位置
	_camera->lookAt(Vec3(0, 0, 0));
	_camera->setCameraFlag(CameraFlag::USER1);
	layer3D->addChild(_camera);
	layer3D->setCameraMask(2);

	auto textureCube = TextureCube::create("skybox/left.jpg", "skybox/right.jpg",
		"skybox/top.jpg", "skybox/bottom.jpg",
		"skybox/front.jpg", "skybox/back.jpg");

	//设置纹理参数
	Texture2D::TexParams tRepeatParams;
	tRepeatParams.magFilter = GL_LINEAR;
	tRepeatParams.minFilter = GL_LINEAR;
	tRepeatParams.wrapS = GL_CLAMP_TO_EDGE;
	tRepeatParams.wrapT = GL_CLAMP_TO_EDGE;
	textureCube->setTexParameters(tRepeatParams);
	//创建天空盒对象
	auto skyBox = Skybox::create();
	skyBox->setTexture(textureCube);
	skyBox->setCameraMask(2);
	layer3D->addChild(skyBox);

	auto sprite3D = Sprite3D::create("qiu.c3b");
	_sprite3D = sprite3D;
	sprite3D->setScale(0.3);
	sprite3D->setCameraMask(2);
	layer3D->addChild(sprite3D);
	//创建一个GL编程的状态通过shader
	auto shader = GLProgramState::create(GLProgram::createWithFilenames("Lession27.vert", "Lession27.frag"));
	shader->setUniformTexture("u_cubeTex", textureCube);
	shader->applyUniforms();
	sprite3D->setGLProgramState(shader);

	//添加触摸监听事件
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(Lession27::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(Lession27::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(Lession27::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;

}

void Lession27::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{

}

void Lession27::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
	if (touches.size()){
		auto touch = touches[0];
		auto delta = touch->getDelta();
		static float angle = 0;
		angle -= CC_DEGREES_TO_RADIANS(delta.x);
		if (_camera){
			_camera->setPosition3D(Vec3(50 * sinf(angle), 0.0f, 50 * cosf(angle)));
			_camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
		}
	}
}

void Lession27::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{

}
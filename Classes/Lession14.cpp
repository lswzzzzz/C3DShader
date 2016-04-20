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

	////�õ���Ļ�ߴ�
	auto s = Director::getInstance()->getWinSize();
	//����3D�����
	auto _camera = cocos2d::Camera::createPerspective(60, (GLfloat)s.width / s.height, 1, 1000);
	//����������۾�λ��
	_camera->setPosition3D(Vec3(0, 50, 50));
	//����������۲��λ��
	_camera->lookAt(Vec3(0, 0, 0));
	_camera->setCameraFlag(CameraFlag::USER1);
	addChild(_camera);

	//������̬ģ��
	auto spriteStatic3D = Sprite3D::create("qiu.c3t");
	_sprite3D = spriteStatic3D;
	spriteStatic3D->setCameraMask(2);
	spriteStatic3D->setScale(0.5);
	spriteStatic3D->setPosition3D(Vec3(0, 0, 0));
	spriteStatic3D->setRotation3D(Vec3(0, 0, 0));
	//���ò�ʹ�õƹ���
	spriteStatic3D->setLightMask(0);
	addChild(spriteStatic3D);

	//����Shader
	GLProgramState*	_pProgramState = GLProgramState::create(GLProgram::createWithFilenames("Lession14.vert", "Lession14.frag"));
	_pProgramState->setUniformVec4("u_color", Vec4(1.0, 0.0, 1.0, 1.0));
	_pProgramState->applyUniforms();
	spriteStatic3D->setGLProgramState(_pProgramState);

    return true;
}
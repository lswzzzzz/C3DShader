#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Lession24 : public cocos2d::Layer
{
public:
	
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	CREATE_FUNC(Lession24);

private:
	//����һ��3D��̬ģ��
	cocos2d::Sprite3D*			_sprite3D;
};

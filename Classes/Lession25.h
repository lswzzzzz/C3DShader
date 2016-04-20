#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Lession25 : public cocos2d::Layer
{
public:
	
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	CREATE_FUNC(Lession25);

private:
	//声明一个3D静态模型
	cocos2d::Sprite3D*			_sprite3D;
};

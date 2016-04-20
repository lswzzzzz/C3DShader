#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Lession11 : public cocos2d::Layer
{
public:
	
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	CREATE_FUNC(Lession11);
private:
	Sprite* m_sprite;
};

#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Lession10 : public cocos2d::Layer
{
public:
	
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	CREATE_FUNC(Lession10);
private:
	Sprite* m_sprite;
};

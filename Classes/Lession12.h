#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Lession12 : public cocos2d::Layer
{
public:
	
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	CREATE_FUNC(Lession12);
private:
	Sprite* m_sprite;
};

#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Lession6 : public cocos2d::Layer
{
public:
	
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	CREATE_FUNC(Lession6);

	void UpdateTexUVAni(float dt);
private:
	Sprite* m_sprite;
	Vec2 m_TexUVAni;
};

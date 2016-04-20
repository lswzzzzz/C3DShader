#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Lession8 : public cocos2d::Layer
{
public:
	
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	CREATE_FUNC(Lession8);
	void UpdateMSK(float dt);
	void UpdateMSK2(float dt);
private:
	Sprite* m_sprite;
	float m_time;
	float blockSize;
};

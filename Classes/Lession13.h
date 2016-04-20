#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Lession13 : public cocos2d::Layer
{
public:
	
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	CREATE_FUNC(Lession13);

	void UpdateLight(float dt);

private:
	Sprite* m_sprite;
	//点光的位置
	cocos2d::Vec2 m_LightPos[2];
	//点光的强度
	float m_LightRange[2];
	//点光的色彩
	cocos2d::Vec4 m_LightColor[2];
	//time
	float m_fTime;
};

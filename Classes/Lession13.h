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
	//����λ��
	cocos2d::Vec2 m_LightPos[2];
	//����ǿ��
	float m_LightRange[2];
	//����ɫ��
	cocos2d::Vec4 m_LightColor[2];
	//time
	float m_fTime;
};

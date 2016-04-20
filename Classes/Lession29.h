#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Lession29 : public cocos2d::Layer
{
public:
	
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	CREATE_FUNC(Lession29);
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
private:
	//声明一个3D摄像机
	cocos2d::Camera* _camera;
	//摄像机触摸旋转角度
	float _angle;
	//声明一个动画模型
	cocos2d::Sprite3D* _spriteAni3D;
};

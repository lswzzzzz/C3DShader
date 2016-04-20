#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Lession28 : public cocos2d::Layer
{
public:
	
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	CREATE_FUNC(Lession28);

	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
private:
	//����һ��3D�����
	cocos2d::Camera* _camera;
	//����һ����̬ģ��
	cocos2d::Node*	_sprite3D;
};

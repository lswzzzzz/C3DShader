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
	//����һ��3D�����
	cocos2d::Camera* _camera;
	//�����������ת�Ƕ�
	float _angle;
	//����һ������ģ��
	cocos2d::Sprite3D* _spriteAni3D;
};

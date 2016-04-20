#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Lession20 : public cocos2d::Layer
{
public:
	
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	CREATE_FUNC(Lession20);

	//更新眼睛色彩的函数
	void UpdateEyeColor(float dt);

private:
	//声明一个3D静态模型
	cocos2d::Sprite3D* _sprite3D;
	cocos2d::GLProgramState* _pProgramState;
	float m_fTime;

};

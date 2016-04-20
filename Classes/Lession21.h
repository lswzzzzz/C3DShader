#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Lession21 : public cocos2d::Layer
{
public:
	
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	CREATE_FUNC(Lession21);

	// 定时刷新函数,旋转球体
	void	RotateQiu(float dt);

private:
	//声明一个3D静态模型
	cocos2d::Sprite3D*			_sprite3D;
	//方向光
	cocos2d::Vec3				_LightDir;
	//旋转角度
	float						_RotateY;
	//Shader状态管理器
	cocos2d::GLProgramState*	_pProgramState;
};

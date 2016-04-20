#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Lession23 : public cocos2d::Layer
{
public:
	
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	CREATE_FUNC(Lession23);

	// 定时刷新函数,旋转球体
	void	RotateQiu(float dt);

private:
	//声明一个3D静态模型
	cocos2d::Sprite3D*			_sprite3D;
	//旋转角度
	float						_RotateY;
	//Shader状态管理器
	cocos2d::GLProgramState*	_pProgramState;
	//点光位置数组
	cocos2d::Vec3				_PointLightPositionArray[3];
	//点光强度数组
	float						_PointLightRangeArray[3];
	//点光颜色数组
	cocos2d::Vec3				_PointLightColorArray[3];
};

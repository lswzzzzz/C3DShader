#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Lession21 : public cocos2d::Layer
{
public:
	
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	CREATE_FUNC(Lession21);

	// ��ʱˢ�º���,��ת����
	void	RotateQiu(float dt);

private:
	//����һ��3D��̬ģ��
	cocos2d::Sprite3D*			_sprite3D;
	//�����
	cocos2d::Vec3				_LightDir;
	//��ת�Ƕ�
	float						_RotateY;
	//Shader״̬������
	cocos2d::GLProgramState*	_pProgramState;
};

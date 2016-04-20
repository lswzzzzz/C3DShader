#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Lession23 : public cocos2d::Layer
{
public:
	
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	CREATE_FUNC(Lession23);

	// ��ʱˢ�º���,��ת����
	void	RotateQiu(float dt);

private:
	//����һ��3D��̬ģ��
	cocos2d::Sprite3D*			_sprite3D;
	//��ת�Ƕ�
	float						_RotateY;
	//Shader״̬������
	cocos2d::GLProgramState*	_pProgramState;
	//���λ������
	cocos2d::Vec3				_PointLightPositionArray[3];
	//���ǿ������
	float						_PointLightRangeArray[3];
	//�����ɫ����
	cocos2d::Vec3				_PointLightColorArray[3];
};

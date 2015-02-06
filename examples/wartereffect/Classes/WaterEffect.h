/**
*@file BAWaterEffect.h
*@brie 播放水纹特效
*
*详细概述
*
*@author DionysosLai，email: 906391500@qq.com
*@version 1.0
*@data 2014-5-15 9:40
*/

#ifndef __WATER_EFFECT_H__
#define __WATER_EFFECT_H__

#include "cocos2d.h"  
#include "cocos-ext.h"

class WaterEffect : public cocos2d::CCNode  
{  
public:  
	WaterEffect();  
	~WaterEffect();  

	static WaterEffect* create();  
	virtual bool init();  

private:   
	void initData();  
	cocos2d::extension::CCArmature*	createArmature(const char* armatureName, const char* armatureProName);
	void onPlayEffect( cocos2d::extension::CCArmature *pArmature, cocos2d::extension::MovementEventType eventType, const char *animationID );
private:  
	cocos2d::extension::CCArmature* m_arEffect;
public:
	void playEffect(void);

};  

#endif /* defined(__WATER_EFFECT_H__) */  
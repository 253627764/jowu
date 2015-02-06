#include "WaterEffect.h"

USING_NS_CC;
//using namespace cocos2d::ui;
using namespace cocos2d::extension;

WaterEffect::WaterEffect()
{

}

WaterEffect::~WaterEffect()
{

}

WaterEffect* WaterEffect::create()
{
	WaterEffect *pNode = new WaterEffect();  
	if (pNode && pNode->init())  
	{  
		pNode->autorelease();  
		return pNode;  
	}  
	CC_SAFE_DELETE(pNode);  
	return NULL;  
}

bool WaterEffect::init()
{
	if (!CCNode::init())  
	{  
		return false;  
	}  
	initData();  
	return true;  
}

void WaterEffect::initData()
{
	m_arEffect = this->createArmature("WaterAnimation/WaterAnimation.ExportJson", "WaterAnimation");
	m_arEffect->setPosition(ccp(0.f, 0.f));
	this->addChild(m_arEffect, 0);
}

cocos2d::extension::CCArmature* WaterEffect::createArmature( const char* armatureName, const char* armatureProName )
{
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(armatureName);
	CCArmature *armature = CCArmature::create(armatureProName);
	return armature;
}

///@brief ����ˮ��Ч��
///@param[in] 
///@return 
///@author DionysosLai,906391500@qq.com 
///@retval  
///@post 
///@version 1.0 
///@data 2014-5-15 10:22
void WaterEffect::playEffect( void )
{
	m_arEffect->getAnimation()->play("Water_Play");
	m_arEffect->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(WaterEffect::onPlayEffect));
}

///@brief ���ˮ��Ч���Ƿ���
///@param[in] 
///@return 
///@author DionysosLai,906391500@qq.com 
///@retval  
///@post 
///@version 1.0 
///@data 2014-5-15 10:23
void WaterEffect::onPlayEffect( cocos2d::extension::CCArmature *pArmature, cocos2d::extension::MovementEventType eventType, const char *animationID )
{
	/// COMPLETE--ֻ���ڶ�������Ϊ��ѭ������ʱ���ڶ���������Ӧһ��
	if (eventType == COMPLETE)
	{
		this->removeAllChildren();
	}
}

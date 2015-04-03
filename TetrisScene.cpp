#include "TetrisScene.h"
#include "SimpleAudioEngine.h"

#include "TetrisLayer.h"
#include "OperateLayer.h"
using namespace cocos2d;
#include "TetrisScene.h"

bool TetrisScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    
	m_gameLayer = TetrisLayer::create();
	m_operateLayer = OperateLayer::create();
	
	m_operateLayer->setPanel(m_gameLayer->getPanel());
	//add audio
	this->addChild(m_gameLayer, 0);
	this->addChild(m_operateLayer, 1);
    return true;
}
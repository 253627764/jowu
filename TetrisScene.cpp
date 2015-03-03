#include "TetrisScene.h"
#include "SimpleAudioEngine.h"

#include "TetrisLayer.h"

using namespace cocos2d;
#include "TetrisScene.h"

bool TetrisScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    
	//add audio
	this->addChild(TetrisLayer::create());
    return true;
}
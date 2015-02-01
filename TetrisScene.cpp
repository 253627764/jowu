#include "TetrisScene.h"
#include "SimpleAudioEngine.h"

#include "TetrisLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

cocos2d::Scene* TetrisScene::createScene()
{
    auto scene = Scene::create();
    //auto layer = Layer::create();
    //scene->addchild(layer);
    return scene;
}

bool TetrisScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    //add sth
    return true;
}

void TetrisScene::menuCloseCallback(cocos2d::Ref* pSender)
{
    
}

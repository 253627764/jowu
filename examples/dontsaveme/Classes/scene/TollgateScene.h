/*
        文件名：    TollgateScene.h
        描　述：    关卡场景
        创建人：    笨木头_钟迪龙 (博客：http://www.benmutou.com)

        创建日期：  2014.4.6
*/
#ifndef TollgateScene_H
#define TollgateScene_H

#include "editor-support/cocostudio/CCSGUIReader.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio;

#include "cocos2d.h"
USING_NS_CC;

class BackgroundLayer;
class Player;
class MonsterLayer;
class TollgateScene : public Layer
{
public:
    ~TollgateScene();
    static Scene* scene();
    CREATE_FUNC(TollgateScene);
    virtual bool init();

    virtual void onExit() override;
private:
    void logic(float dt);

    /* 创建操作UI */
    void createOprUI();

    void moveToLeft(Ref* sender, TouchEventType type);
    void moveToRight(Ref* sender, TouchEventType type);
    void quickMove(Ref* sender, TouchEventType type);

    /* 碰撞检测 */
    bool onContactBegin(PhysicsContact& contact);

    BackgroundLayer* m_backgroundLayer;
    Player* m_player;
    MonsterLayer* m_monsterLayer;
};

#endif
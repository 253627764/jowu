#include "TollgateScene.h"
#include "BackgroundLayer.h"
#include "entity\Player.h"
#include "ObjectTag.h"
#include "MonsterLayer.h"
#include "entity\Monster.h"

TollgateScene::~TollgateScene()
{

}

Scene* TollgateScene::scene()
{
    auto scene = Scene::createWithPhysics();

    /* 微重力世界 */
    Vect gravity(0, -0.5f);
    scene->getPhysicsWorld()->setGravity(gravity);

    /* 开启测试模式 */
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    //创建一个边界
    Size visibleSize = Director::getInstance()->getVisibleSize();

    /* 
        创建一个空心盒子刚体，作为我们游戏世界的边界（避免游戏内的物体跑出屏幕） 
        参数分别是刚体大小、材质（其实就是一些预设的配置数据）、边线厚度
    */
    auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);

    /* 创建一个节点，用于承载刚体，这样刚体就能参与到游戏的物理世界 */
    auto node = Node::create();
    node->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    node->setPhysicsBody(body);
    scene->addChild(node);

    /* 背景层 */
    auto backgroundLayer = BackgroundLayer::create();
    scene->addChild(backgroundLayer, 0);

    /* 怪物层 */
    auto monsterLayer = MonsterLayer::create();
    scene->addChild(monsterLayer, 1);

    auto layer = TollgateScene::create();
    scene->addChild(layer, 10);

    layer->m_backgroundLayer = backgroundLayer;
    layer->m_monsterLayer = monsterLayer;
    return scene;
}


bool TollgateScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    /* 创建主角 */
    Size visibleSize = Director::getInstance()->getVisibleSize();

    m_player = Player::create();
    m_player->setPosition(Point(visibleSize.width * 0.5f, visibleSize.height * 0.85f));
    this->addChild(m_player, 5);

    /* 创建操作UI */
    createOprUI();

    /* 碰撞监听 */
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(TollgateScene::onContactBegin, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);


    this->schedule(schedule_selector(TollgateScene::logic));
    return true;
}

void TollgateScene::onExit()
{
    Layer::onExit();

    _eventDispatcher->removeEventListenersForTarget(this);
}

void TollgateScene::logic(float dt)
{
    m_backgroundLayer->logic(dt);
    m_monsterLayer->logic(dt);
}

void TollgateScene::createOprUI()
{
    auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("OprUI_1.ExportJson");
    this->addChild(UI);

    /* 获取按钮对象 */
    Button* rightBtn = (Button*)Helper::seekWidgetByName(UI, "rightBtn");
    Button* quickMoveBtn = (Button*)Helper::seekWidgetByName(UI, "quickMoveBtn");
    Button* leftBtn = (Button*)Helper::seekWidgetByName(UI, "leftBtn");

    /* 添加按钮回调事件 */
    leftBtn->addTouchEventListener(this, toucheventselector(TollgateScene::moveToLeft));
    rightBtn->addTouchEventListener(this, toucheventselector(TollgateScene::moveToRight));
    quickMoveBtn->addTouchEventListener(this, toucheventselector(TollgateScene::quickMove));

}

void TollgateScene::moveToLeft(Ref* sender, TouchEventType type)
{
    switch (type)
    {
    case TOUCH_EVENT_ENDED:
        m_player->moveToLeft();
        break;

    }
}

void TollgateScene::moveToRight(Ref* sender, TouchEventType type)
{
    switch (type)
    {
    case TOUCH_EVENT_ENDED:
        m_player->moveToRight();
        break;

    }
}

void TollgateScene::quickMove(Ref* sender, TouchEventType type)
{
    switch (type)
    {
    case TOUCH_EVENT_ENDED:
        m_player->quickMove();
        break;

    }
}

bool TollgateScene::onContactBegin(PhysicsContact& contact)
{
    auto nodeA = (Sprite*)contact.getShapeA()->getBody()->getNode();
    auto nodeB = (Sprite*)contact.getShapeB()->getBody()->getNode();

    if (nodeA == NULL || nodeB == NULL)
    {
        return true;
    }

    Node* playerNode = NULL;    /* 玩家对象 */
    Node* other = NULL;         /* 怪物或墙等其他对象 */

    if (nodeA->getTag() == ObjectTag_Player)
    {
        playerNode = nodeA;
        other = nodeB;
    }
    else if (nodeB->getTag() == ObjectTag_Player)
    {
        playerNode = nodeB;
        other = nodeA;
    }
    else
    {
        /* 如果两个碰撞的物体中，不存在玩家对象，就忽略，不做处理 */
        return true;
    }

    Player* player = (Player*)playerNode;

    /* 碰撞到边缘锯齿（墙），+1血 */
    if (other->getTag() == ObjectTag_Border)
    {
        /* 扣-1血，就相当于加1血 */
        player->beAtked(-1);

        log("player cur HP:%d", player->getiHP());
    }
    else if (other->getTag() == ObjectTag_Monster)
    {
        /* 碰撞到怪物，根据怪物的属性进行操作 */
        Monster* monster = (Monster*)other;

        if (monster->getiAtk() != 0)
        {
            /* 攻击玩家（可能是加血） */
            player->beAtked(monster->getiAtk());

            /* 碰撞之后，怪物消失 */
            monster->removeFromParent();
        }
    }
    return true;
}



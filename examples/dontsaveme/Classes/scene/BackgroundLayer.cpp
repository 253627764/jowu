#include "BackgroundLayer.h"
#include "ObjectTag.h"
//#include "ObjectTag.h"

BackgroundLayer::BackgroundLayer()
{
}

BackgroundLayer::~BackgroundLayer()
{
}

bool BackgroundLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();

    /* 背景图片 */
    m_bg1 = Sprite::create("background.jpg");
    m_bg1->setPosition(Point(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
    this->addChild(m_bg1);

    m_bg2 = Sprite::create("background.jpg");
    m_bg2->setPosition(Point(visibleSize.width * 0.5f, -visibleSize.height * 0.5f));
    this->addChild(m_bg2);

    /* 创建边缘锯齿 */
    auto border = Sprite::create("border.png");
    Size borderSize = border->getContentSize();

    auto border1 = createBorder(Point(borderSize.width * 0.5f, borderSize.height * 0.5f));
    this->addChild(border1);

    auto border2 = createBorder(Point(visibleSize.width - borderSize.width * 0.5f, borderSize.height * 0.5f));
    border2->setFlippedX(true);
    this->addChild(border2);

    auto border3 = createBorder(Point(visibleSize.width * 0.5f, visibleSize.height * 0.15f));
    borderSize = border3->getContentSize();
    border3->setRotation(90.0f);
    this->addChild(border3);

//     border1->setTag(ObjectTag_Border);
//     border2->setTag(ObjectTag_Border);
//     border3->setTag(ObjectTag_Border);
    return true;
}

Sprite* BackgroundLayer::createBorder(Point pos)
{
    auto border = Sprite::create("border.png");

    Size borderSize = border->getContentSize();

    auto body = PhysicsBody::createBox(borderSize);
    body->setDynamic(false);
    body->setCategoryBitmask(1);    // 0001
    body->setCollisionBitmask(1);   // 0001
    body->setContactTestBitmask(1); // 0001
    border->setPhysicsBody(body);
    border->setPosition(pos);

    border->setTag(ObjectTag_Border);
    return border;
}

void BackgroundLayer::logic(float dt) {
    int posY1 = m_bg1->getPositionY();	// 背景地图1的Y坐标
    int posY2 = m_bg2->getPositionY();	// 背景地图2的Y坐标

    int iSpeed = 3;	// 地图滚动速度

    /* 两张地图向上滚动（两张地图是相邻的，所以要一起滚动，否则会出现空隙） */
    posY1 += iSpeed;
    posY2 += iSpeed;

    /* 屏幕宽 */
    int iVisibleHeight = Director::getInstance()->getVisibleSize().height;

    /* 当第1个地图完全离开屏幕时，让第2个地图完全出现在屏幕上，同时让第1个地图紧贴在第2个地图后面 */
    if (posY1 > iVisibleHeight * 1.5f) {
        posY2 = iVisibleHeight * 0.5f;
        posY1 = -iVisibleHeight * 0.5f;
    }
    /* 同理，当第2个地图完全离开屏幕时，让第1个地图完全出现在屏幕上，同时让第2个地图紧贴在第1个地图后面 */
    if (posY2 > iVisibleHeight * 1.5f) {
        posY1 = iVisibleHeight * 0.5f;
        posY2 = -iVisibleHeight * 0.5f;
    }

    m_bg1->setPositionY(posY1);
    m_bg2->setPositionY(posY2);
}

#include "Player.h"
#include "scene\ObjectTag.h"

Player::Player()
{
    m_iHP = 100;
}

Player::~Player()
{
}

bool Player::init()
{
    auto playerSp = Sprite::create("player.png");
    this->addChild(playerSp);

    auto body = PhysicsBody::createCircle(playerSp->getContentSize().width * 0.4f);
    body->getShape(0)->setFriction(0);
    body->getShape(0)->setRestitution(1.0f);
    body->setCategoryBitmask(1);    // 0001
    body->setCollisionBitmask(1);   // 0001
    body->setContactTestBitmask(1); // 0001
    this->setPhysicsBody(body);

    /* 给角色添加推力 */
    this->getPhysicsBody()->applyImpulse(Vect(0, -40000));

    this->setTag(ObjectTag_Player);
    return true;
}

void Player::moveToRight()
{
    this->getPhysicsBody()->applyImpulse(Vect(50000, 0));
}

void Player::moveToLeft()
{
    this->getPhysicsBody()->applyImpulse(Vect(-50000, 0));
}

void Player::quickMove()
{
    /* 放屁技能，强力的向下推力 */
    this->getPhysicsBody()->applyImpulse(Vect(0, -200000));
}

void Player::beAtked(int iValue)
{
    if (iValue < 0)
    {
        cure(-iValue);
    }
    else
    {
        hurt(std::abs(iValue));
    }
//     if (getiHP() <= 0)
//     {
//         NOTIFY->postNotification("mdGameWin");
//     }
}

void Player::hurt(int iValue)
{
    setiHP(getiHP() - iValue);
}

void Player::cure(int iValue)
{
    setiHP(getiHP() + iValue);
}

void Player::logic(float dt)
{
}

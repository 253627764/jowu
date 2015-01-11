/*
    文件名：    Player.h
    描　述：
    创建人：    笨木头_钟迪龙 (博客：http://www.benmutou.com)

    创建日期：  2014.4.7
*/
#ifndef Player_H
#define Player_H

#include "cocos2d.h"
USING_NS_CC;

class Player : public Node
{
public:
    Player();
    ~Player();
    CREATE_FUNC(Player);
    virtual bool init();

    void moveToRight();
    void moveToLeft();
    void quickMove();

    void logic(float dt);

    /* 受伤害，或者治愈 */
    void beAtked(int iValue);

private:
    CC_SYNTHESIZE(int, m_iHP, iHP);

    /* 受伤害 */
    void hurt(int iValue);

    /* 治愈 */
    void cure(int iValue);
};

#endif
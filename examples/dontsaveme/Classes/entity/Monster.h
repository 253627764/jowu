/*
	文件名：    Monster.h
	描　述：  
	创建人：    笨木头_钟迪龙 (博客：http://www.benmutou.com)

	创建日期：  2014.4.8
*/
#ifndef Monster_H
#define Monster_H

#include "cocos2d.h"
USING_NS_CC;

class Monster : public Node 
{
public:
	Monster();
	~Monster();
    static Monster* create(int ID);
    bool init(int ID);

    /* 加入到当前场景的物理世界 */
    void joinToWorld(Node* parent);

    CC_SYNTHESIZE(int, m_ID, ID);
    CC_SYNTHESIZE(int, m_iPosX, iPosX);
    CC_SYNTHESIZE(int, m_iPosY, iPosY);
    CC_SYNTHESIZE(int, m_iAtk, iAtk);
    CC_SYNTHESIZE(float, m_fShowTime, fShowTime);
    CC_SYNTHESIZE(Value, m_sModelPath, sModelPath);
};

#endif
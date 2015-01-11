/*
	文件名：    MonsterLayer.h
	描　述：  
	创建人：    笨木头_钟迪龙 (博客：http://www.benmutou.com)

	创建日期：  2014.4.8
*/
#ifndef MonsterLayer_H
#define MonsterLayer_H

#include "cocos2d.h"
USING_NS_CC;

class Monster;
class MonsterLayer : public Layer 
{
public:
	MonsterLayer();
	~MonsterLayer();
	CREATE_FUNC(MonsterLayer);
	virtual bool init();

    void logic(float dt);
private:
    /* 从配置文件中加载怪物数据 */
    void loadMonstersFromTmxConf();

    /* 存放所有即将要出场的怪物对象 */
    Vector<Monster*> m_monsterVec;

    /* 计时器 */
    float m_fTimeCounter;
};

#endif
/*
	文件名：    BackgroundLayer.h
	描　述：  
	创建人：    笨木头_钟迪龙 (博客：http://www.benmutou.com)

	创建日期：  2014.4.7
*/
#ifndef BackgroundLayer_H
#define BackgroundLayer_H

#include "cocos2d.h"
USING_NS_CC;

class BackgroundLayer : public Layer 
{
public:
	BackgroundLayer();
	~BackgroundLayer();
	CREATE_FUNC(BackgroundLayer);
	virtual bool init();

    void logic(float dt);
private:
    Sprite* m_bg1;
    Sprite* m_bg2;

    Sprite* createBorder(Point pos);
};

#endif
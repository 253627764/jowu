#ifndef OPERATELAYER_H
#define OPERATELAYER_H
using namespace cocos2d;
#include "cocos2d.h"
class GamePanel;
class OperateLayer : public cocos2d::Layer
{
public:
	OperateLayer();
	static OperateLayer* create();
	virtual bool init();
	void setPanel(GamePanel* panel) { m_panel = panel; }
	//enable touch for further use
	//virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
 //   virtual void onTouchMoved(Touch *touch, Event *unused_event); 
 //   virtual void onTouchEnded(Touch *touch, Event *unused_event); 
 //   virtual void onTouchCancelled(Touch *touch, Event *unused_event);

	//virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
 //   virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
 //   virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
 //   virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event);

	//enable key for test in pc
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

private:
	GamePanel* m_panel;
};

#endif
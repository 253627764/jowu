#include "GamePanel.h"
#include "OperateLayer.h"
#include "base/CCEventKeyboard.h"

OperateLayer::OperateLayer()
	: m_panel(nullptr) 
{
}

OperateLayer* OperateLayer::create()
{
	OperateLayer* ret = new OperateLayer();
	if (ret && ret->init()) {
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	return ret;
}

bool OperateLayer::init()
{
	setTouchEnabled(true);
	setKeyboardEnabled(true);
	return true;
}

void OperateLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		{
			m_panel->moveLeft();
		}
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		{
			m_panel->moveRight();
		}
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		{
			m_panel->rotate(true);
		}
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		{
			m_panel->down();
		}
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		{
			m_panel->drop();
		}
		break;

	case EventKeyboard::KeyCode::KEY_F2:
		{
			m_panel->reStart();
		}
		break;
	case EventKeyboard::KeyCode::KEY_ENTER:
		{
			m_panel->pause();
		}
		break;

	}
}

bool OperateLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	return false;
}
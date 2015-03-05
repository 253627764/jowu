#include "TetrisLayer.h"
#include "Piece.h"

bool TetrisLayer::init()
{
	if (!Layer::create()) {
		return false; 
	}

	Sprite* s = Sprite::initWithFile("darkBlue.png");
	s->setContentSize(Size(20, 20));
	addChild(s);
	s->setPosition(0 , 0);
	m_panel = GamePanel::create();
	addChild(m_panel);
	return true;
}

bool TetrisLayer::onTouchBegan(Touch* touch, Event* event)
{
	return false;
}

void TetrisLayer::update(float delat)
{
	if (m_panel) {
		m_panel->updatePiece(delat);
	}
}

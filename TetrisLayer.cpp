#include "TetrisLayer.h"
#include "Piece.h"

bool TetrisLayer::init()
{
	if (!Layer::create()) {
		return false; 
	}

	Sprite* s = Sprite::create("darkBlue.png");
	//CCLOG("sprite size [%f %f]", s->getContentSize().width, s->getContentSize().height);
	////s->setContentSize(Size(20, 20));
	//s->setScale(0.2);
	//CCLOG("sprite size [%f %f]", s->getContentSize().width, s->getContentSize().height);
	//addChild(s);
	/*s->setPosition(100 , 100);*/
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

void TetrisLayer::runThisTest()
{
		
}

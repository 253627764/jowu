#include "TetrisLayer.h"
#include "Piece.h"

bool TetrisLayer::init()
{
	if (!Layer::create()) {
		return false; 
	}

	Sprite* s = Sprite::create("darkBlue.png");
	m_panel = GamePanel::create();
	addChild(m_panel);
    schedule(schedule_selector(TetrisLayer::tick), 0.5);
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

void TetrisLayer::tick(float delta)
{
	if (m_panel) {
		m_panel->down();
	}
}

void TetrisLayer::runThisTest()
{

}

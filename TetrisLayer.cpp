#include "TetrisLayer.h"
#include "Piece.h"

bool TetrisLayer::init()
{
	GamePanel::create();


	return true;
}

TetrisLayer::~TetrisLayer()
{
	if (m_panel) {
		delete m_panel;
		m_panel = nullptr;
	}
}

bool TetrisLayer::addBlockToPanel(TetrisBlock *block, const JJPoint &pos)
{
	if (!m_panel || !block) return false;
	return m_panel->addBlockToPanel(block, pos);
}

bool TetrisLayer::down()
{
	if (!m_panel) return false;
	return m_panel->down();
}

bool TetrisLayer::moveLeft()
{
	if (!m_panel) return false;
	return m_panel->moveLeft();
}

bool TetrisLayer::moveRight()
{
	if (!m_panel) return false;
	return m_panel->moveRight();
}

bool TetrisLayer::rotate(bool clockWise)
{
	if (!m_panel) return false;
	return m_panel->rotate(clockWise);
}

bool TetrisLayer::drop()
{
	if (!m_panel) return false;
	return m_panel->drop();
}

TetrisBlock* TetrisLayer::block()
{
	if (!m_panel) return nullptr;
	return m_panel->block();
}
JJPoint TetrisLayer::position()
{
	if (!m_panel) return JJPoint(-1, -1);
	return m_panel->position();
}
unsigned int TetrisLayer::speed()
{
	if (!m_panel) return -1;
	return m_panel->speed();
}
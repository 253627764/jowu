#include "TetrisLayer.h"
#include "Piece.h"

bool TetrisLayer::addBlockToPanel(TetrisBlock *block, const JJPoint &pos)
{
	if (m_panel) {
		return m_panel->update(block, pos);
	}

	return false;
}

bool TetrisLayer::down()
{
	if (m_block && m_panel) {
		if (m_panel->checkPosition(m_block, JJPoint(m_pos.x, m_pos.y + 1))) {
			++m_pos.y;
			m_block->locate(m_pos.x, m_pos.y + 1);
			return true;
		}
	}

	return false;
}

bool TetrisLayer::moveLeft()
{
	if (m_block && m_panel) {
		if (m_panel->checkPosition(m_block, JJPoint(m_pos.x - 1, m_pos.y))) {
			--m_pos.x;
			m_block->locate(m_pos.x - 1, m_pos.y);
			return true;
		}
	}

	return false;
}

bool GamePanel::moveRight()
{
	if (m_block && m_panel) {
		if (m_panel->checkPosition(m_block, JJPoint(m_pos.x + 1, m_pos.y))) {
			++m_pos.x;
			m_block->locate(m_pos.x + 1, m_pos.y);
			return true;
		}
	}

	return false;
}

bool GamePanel::rotate(bool clockWise)
{
	TetrisBlock* block;
	
	if (m_block && m_panel) {
		
        int offset;
		for (offset = 0; offset < PanelWidth; ++offset) {
			if (m_panel->checkPosition(block, JJPoint((m_pos.x + offset) % PanelWidth, m_pos.y))) {
				break;
			}
		}
		//debug!!
		m_pos.x = (m_pos.x + offset) % PanelWidth;
		m_block = block;
	}

	return false;
}

void GamePanel::drop()
{
	int i;
	for (i = 0; i < PanelHeight - m_pos.y; ++i) {
		if (!m_panel->checkPosition(m_block,
			JJPoint(m_pos.x, m_pos.y + i))) {
			break;
		}
	}

	m_pos.y += i;
	//add block to panel
	//addBlockToPanel();
}

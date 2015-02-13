#include "GamePanel.h"
#include "Piece.h"

GamePanel::GamePanel(unsigned int width, unsigned int height)
	: m_width(PanelWidth), m_height(PanelHeight)
{
	m_pieces = new Piece*[m_height];
    for (int i = 0; i < m_height; ++i) {
        m_pieces[i] = new Piece[m_width];
    }
    
	if (!m_data.empty()) m_data.clear();

	for (int i = 0; i < m_height; i++) {
		m_data.push_back(0);
    }
}

GamePanel* GamePanel::instance()
{
	if (!s_instance) {
		s_instance = new GamePanel();
	}

	return s_instance;
}

void GamePanel::destory()
{
	if (s_instance) {
		delete s_instance;
		s_instance = NULL;
	}
}

bool GamePanel::checkPosition(TetrisBlock* block, const JJPoint& pos)
{
	if (!block) {
		return false;
	}
#if 1//NonBinary
	int i;
	for (i = 0; i < block->pieces().size(); ++i) {
		int _x = block->onePiece(i)->offset().x + pos.x;
		int _y = block->onePiece(i)->offset().y + pos.y;
		if (0 > _x || PanelWidth < _x || 0 > _y || PanelHeight < _y) {
			return false;
		}
		
		if (State_Hollow != m_pieces[_x][_y].State()) {
			return false;
		}
	}

	return true;
#else
//TO DO :Binary option
#endif
}

bool GamePanel::update(TetrisBlock* block, const JJPoint &pos)
{
	if (!block) {
		return false;
	}

	int i;
	for (i = 0; i < block->pieces.size(); ++i) {
		int x = block->pieces()[i]->offset().x + pos.x;
		int y = block->pieces()[i]->offset().y + pos.y;
		if ((0 > x || PanelWidth < x) || (0 > y || PanelHeight < y)) {
			return false;
		}
		
		if (State_Hollow != m_pieces[x][y].State()) {
			return false;
		}

		m_pieces[x][y] = *(block->onePiece(i));
		m_pieces[x][y].setState(State_Fill);
		m_pieces[x][y].setColor(block->color());
	}

	return true;
}
/*
Piece GamePanel::getPiece(unsigned int x, unsigned int y) const
{
	if ((0 <= x && PanelWidth > x) || (0 <= y && PanelHeight > y)) {
		return m_pieces[x][y];
	}

	return Piece();
}*/

void GamePanel::moveByLines(unsigned int form, unsigned int to)
{
	if (PanelHeight <= form || PanelHeight <= to) {
		return;
	}

	for (int i = 0; i < PanelWidth; ++i) {
		m_pieces[i][form].setPositionY(to);
	}
}

std::vector<int> GamePanel::eliminateLines()
{
	std::vector<int> clearLayer;
    int i;
    int j;
	for (i = PanelHeight; i >= 0; --i) {
        bool clear = true;
        for (j = 0;j < PanelWidth; j++) {
            if (State_Fill != m_pieces[i][j].State()) {
                clear = false;
                break;
            }
        }

		if (clear) {
			clearLayer.push_back(i);
		}
    }
    
    return clearLayer;
}

bool GamePanel::elevate(unsigned int lines)
{
	if (PanelHeight >= (currentHeight() + lines)) {
		return false;
	}
	
	//except that i+2 will be overrided, elevate from the top.
	for(int i = PanelHeight - lines; i >= 0 ; --i) {
		moveByLines(i, i + lines);
	}

	return true;
}

//box2d will added further
unsigned int GamePanel::collapse()
{
	int i, j;
	unsigned int dropLine = 0;
	for (i = PanelHeight; i >= 0; --i) {
		if (State_Effect == m_pieces[0][i].State()) {
			++dropLine;
			continue;
		}

		moveByLines(i, i - dropLine);
	}

	for (i = 0; i < dropLine; ++i) {
		for (j = 0; j < PanelWidth; ++j) {
			//m_pieces[i][j]????????(Color_Black); // clear

		}
	}

	return dropLine;
}

void GamePanel::reset()
{
	int i, j;
	for (i = 0; i < PanelHeight; ++i) {
		for (j = 0; j < PanelWidth; ++j) {
			m_pieces[i][j].removeFromParentAndCleanup(false);
		}
	}
}

bool GamePanel::addBlockToPanel(TetrisBlock *block, const JJPoint &pos)
{
	if (m_panel) {
		return m_panel->update(block, pos);
	}

	return false;
}

bool GamePanel::down()
{
	if (m_block) {
		if (m_panel->checkPosition(m_block, JJPoint(m_pos.x, m_pos.y + 1))) {
			++m_pos.y;
			m_block->locate(m_pos.x, m_pos.y + 1);
			return true;
		}
	}

	return false;
}

bool GamePanel::moveLeft()
{
	if (m_block) {
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

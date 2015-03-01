#include "GamePanel.h"
#include "Piece.h"
#include "BlockGroup.h"

#define pixel 20

GamePanel::GamePanel(unsigned int width, unsigned int height)
	: m_width(PanelWidth), m_height(PanelHeight)
{  
	if (!m_data.empty()) m_data.clear();

	for (int i = 0; i < m_height; i++) {
		m_data.push_back(0);
    }
}

GamePanel* GamePanel::create()
{
	GamePanel* ret = new GamePanel();
	if (ret && ret->init()) {
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	return ret;
}

bool GamePanel::init()
{
	memset(m_pieces, 0, sizeof(Piece) * PanelWidth * PanelHeight);
    m_block = BlockGroup::instance()->getBlock();
    for (int i = 0; i < NEXT_BLOCK_COUNT; ++i) {
        m_nextBlocks.push_back(BlockGroup::instance()->getBlock());
    }
    
	return true;
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
		
		if (State_Hollow != m_pieces[_x][_y]->State()) {
			return false;
		}
	}

	return true;
#else
//TO DO :Binary option
#endif
}

bool GamePanel::addBlockToPanel(TetrisBlock* block, const JJPoint &pos)
{
	if (!block) {
		return false;
	}

	int i;
	for (i = 0; i < block->pieces().size(); ++i) {
		int x = block->pieces()[i]->offset().x + pos.x;
		int y = block->pieces()[i]->offset().y + pos.y;
		if ((0 > x || PanelWidth < x) || (0 > y || PanelHeight < y)) {
			return false;
		}
		
		if (State_Hollow != m_pieces[x][y]->State()) {
			return false;
		}

		m_pieces[x][y] = block->onePiece(i);
		m_pieces[x][y]->setState(State_Fill);
		m_pieces[x][y]->setColor(block->color());
	}
    
    
    m_block = m_nextBlocks.front();
    m_nextBlocks.pop_front();
    m_nextBlocks.push_back(BlockGroup::instance()->getBlock());
    
	return true;
}

std::vector<int> GamePanel::eliminateLines()
{
	std::vector<int> clearLayer;
    int i;
    int j;
	for (i = PanelHeight; i >= 0; --i) {
        bool clear = true;
        for (j = 0;j < PanelWidth; j++) {
            if (State_Fill != m_pieces[i][j]->State()) {
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
	return true;
}

unsigned int GamePanel::collapse()
{
    int dropLine = 0;
	int w, h;
	for (h = 0; h < PanelHeight; ++h) {
		//checkout if the line of the height be kill
		bool killed = true;
		for (w = 0; w < PanelWidth; ++w) {
			if (State_Fill != m_pieces[w][h]->State()) {
				killed = false;
				break;
			}
		}

        if (killed) {
            // play animation ~
            m_pieces[w][h]->removeAllChildrenWithCleanup(true);
            ++dropLine;
            
        }
		for (w = 0; w < PanelWidth; ++w) {
			m_pieces[w][h + dropLine]->setDestinationY(h);
			m_pieces[w][h] = m_pieces[w][h + dropLine];
            
		}
	}

	for (h = PanelHeight; h > PanelHeight - dropLine; --h) {
		for (w = 0; w < PanelWidth; ++w) {
			m_pieces[w][h] = nullptr;
		}
	}

	return dropLine;
}

void GamePanel::reset()
{
	int i, j;
	for (i = 0; i < PanelHeight; ++i) {
		for (j = 0; j < PanelWidth; ++j) {
			m_pieces[i][j]->removeFromParentAndCleanup(false);
			m_pieces[i][j] = nullptr;
		}
	}
}

bool GamePanel::down()
{
	if (m_block) {
		if (checkPosition(m_block, JJPoint(m_pos.x, m_pos.y + 1))) {
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
		if (checkPosition(m_block, JJPoint(m_pos.x - 1, m_pos.y))) {
			--m_pos.x;
			m_block->locate(m_pos.x - 1, m_pos.y);
			return true;
		}
	}

	return false;
}

bool GamePanel::moveRight()
{
	if (m_block) {
		if (checkPosition(m_block, JJPoint(m_pos.x + 1, m_pos.y))) {
			++m_pos.x;
			m_block->locate(m_pos.x + 1, m_pos.y);
			return true;
		}
	}

	return false;
}

bool GamePanel::rotate(bool clockWise)
{
	TetrisBlock* block = m_block->rotate(clockWise);
	
	if (m_block) {
		
        int offset;
		for (offset = 0; offset < PanelWidth; ++offset) {
			if (checkPosition(block, JJPoint((m_pos.x + offset) % PanelWidth, m_pos.y))) {
				break;
			}
		}
		//debug!!
		m_pos.x = (m_pos.x + offset) % PanelWidth;
		m_block = block;
	}

	return false;
}

bool GamePanel::drop()
{
	int i;
	for (i = PanelHeight - m_pos.y; i >= 0 ; --i) {
		if (checkPosition(m_block, JJPoint(m_pos.x, i))) {
			continue;
		}

		m_pos.y = i - 1;
		m_block->locate(m_pos.x, i - 1);
		return true;
	}
    
	return false;
}

void GamePanel::adjustPanel()
{
	//
	
}

void GamePanel::moveByLines(unsigned int form, unsigned int to)
{
	if (PanelHeight <= form || PanelHeight <= to) {
		return;
	}

	for (int i = 0; i < PanelWidth; ++i) {
		m_pieces[i][form]->setDestinationY(to);
	}
}
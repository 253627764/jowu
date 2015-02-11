#include "GamePanel.h"
#include "Piece.h"

class PanelData;
PanelData* GetPanelInstance()
{
    return NULL;//PanelData::instance();
}

class PanelData
{
public:
    PanelData(unsigned int width = PanelWidth, unsigned int height = PanelHeight);
    virtual ~PanelData() {}
    static PanelData* instance();
	//inline Piece getPiece(unsigned int x, unsigned int y) const;

    bool update(TetrisBlock* block, const JJPoint &pos);
	bool checkPosition(TetrisBlock* block, const JJPoint& pos);
	std::vector<int> eliminateLines();
	unsigned int collapse();
	void moveByLines(unsigned int form, unsigned int to);
	unsigned int currentHeight() const;
    bool elevate(unsigned int lines);
    void reset();

private:
    static PanelData* s_instance;
private:
	unsigned int m_width;
	unsigned int m_height;
    std::vector<unsigned int> m_data;
    Piece **m_pieces;
};

PanelData::PanelData(unsigned int width, unsigned int height)
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

PanelData* PanelData::instance()
{
	if (!s_instance) {
		s_instance = new PanelData();
	}

	return s_instance;
}

bool PanelData::checkPosition(TetrisBlock* block, const JJPoint& pos)
{
	if (!block) {
		return false;
	}
#if 1//NonBinary
	int i;
	for (i = 0; i < block->Pieces().size(); ++i) {
		int _x = block->Pieces()[i].getPosition().x + pos.x;
		int _y = block->Pieces()[i].getPosition.y + pos.y;
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

bool PanelData::update(TetrisBlock* block, const JJPoint &pos)
{
	if (!block) {
		return false;
	}

	int i;
	for (i = 0; i < block->Pieces().size(); ++i) {
		int x = block->Pieces()[i].x + pos.x;
		int y = block->Pieces()[i].y + pos.y;
		if ((0 > x || PanelWidth < x) || (0 > y || PanelHeight < y)) {
			return false;
		}
		
		if (State_Hollow != m_pieces[x][y].State()) {
			return false;
		}

		m_pieces[x][y].setState(State_Fill);
		m_pieces[x][y].setColor(block->color());
	}

	return true;
}
/*
Piece PanelData::getPiece(unsigned int x, unsigned int y) const
{
	if ((0 <= x && PanelWidth > x) || (0 <= y && PanelHeight > y)) {
		return m_pieces[x][y];
	}

	return Piece();
}*/

void PanelData::moveByLines(unsigned int form, unsigned int to)
{
	if (PanelHeight <= form || PanelHeight <= to) {
		return;
	}

	for (int i = 0; i < PanelWidth; ++i) {
		m_pieces[i][form].setPositionY(to);
	}
}

std::vector<int> PanelData::eliminateLines()
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

bool PanelData::elevate(unsigned int lines)
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
unsigned int PanelData::collapse()
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
			m_pieces[i][j].reset(Color_Black);
		}
	}

	return dropLine;
}

void PanelData::reset()
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
	if (m_block && m_panel) {
		if (m_panel->checkPosition(m_block, JJPoint(m_pos.x, m_pos.y + 1))) {
			++m_pos.y;
			return true;
		}
	}

	return false;
}

bool GamePanel::moveLeft()
{
	if (m_block && m_panel) {
		if (m_panel->checkPosition(m_block, JJPoint(m_pos.x - 1, m_pos.y))) {
			--m_pos.x;
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
			return true;
		}
	}

	return false;
}

bool GamePanel::rotate(bool clockWise)
{
	TetrisBlock* block;
	if (m_block && m_panel) {
		block = clockWise ? m_block->right() : m_block->left();
        int offset;
		for (offset = 0; offset < PanelWidth; ++offset) {
			if (m_panel->checkPosition(block, JJPoint((m_pos.x + offset) % PanelWidth, m_pos.y))) {
				break;
			}
		}

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

#include "GamePanel.h"

class PanelData;
PanelData* GetPanelInstance()
{
    return PanelData::instance();
}

class Piece
{
    JJ_DISCPY(Piece)
public:
    Piece(INT x = -1, INT y = -1, State_Type state = State_Invalid,
		Color_Type color = Color_Invalid)
        : m_x(x), m_y(y), m_state(state), m_color(color) {}
    virtual ~Piece() {}
	inline void reset(Color_Type color) { m_x = -1; m_y = -1;
		m_state = State_Invalid; m_color = color; }

	INT X() const { return m_x; }
    INT Y() const { return m_y; }
    State_Type State() const { return m_state; }
    Color_Type color() const { return m_color; }
	

	void setX(INT x) { m_x = x; }
	void setY(INT y) { m_y = y; }
	void setState(const State_Type& state) { m_state = state; }
	void setColor(const Color_Type& color) { m_color = color; }

private:
    int m_state;//0 null 1 block
    INT m_x;
    INT m_y;
    Color_Type m_color;
};

class PanelData
{
	typedef PanelWidth w;
	typedef PanelHeight h;
public:
    PanelData(INT width = PanelWidth, INT height PanelHeight);
    virtual ~PanelData() {}
    static PanelData* instance();
	inline Piece getPiece(INT x, INT y) const;

    bool update(TetrisBlock* block, const JJPoint &pos);
	bool checkPosition(TetrisBlock* block, const JJPoint& pos);
	std::vecteor<int> eliminateLines();
	void collapse() const;
	void moveByLines(INT form, INT to);
	INT currentHeight() const;

private:
    static PanelData* s_instance;
private:
	INT m_width;
	INT m_height;
    std::vector<INT> m_data;
    Piece m_pieces[PanelWidth][PanelHeight];
};

PanelData::PanelData(INT width = PanelWidth, INT height PanelHeight)
	: m_width(PanelWidth), m_height(PanelHeight)
{
	m_pieces = new Piece[m_width][m_height];
	if (!m_data.empty()) m_data.clear();

	for (int i = 0; i < m_height; i++) {
		m_data.push_back(0);
    }
}

PanelData* PanelData::instance()
{
	if (!s_instance) {
		s_instance = new PanelData(w, h);
	}

	return s_instance;
}

bool PanelData::checkPosition(TetrisBlock* block, const JJPoint& pos)
{
#if 1//NonBinary
	int i;
	for (i = 0; i < block->Points().size(); ++i) {
		int _x = block->Points()[i].x + pos.x;
		int _y = block->Points()[i].y + pos.y;
		if ((0 > x || w < x) || (0 > y || h < y) {
			return false;
		}
		
		if (State_Hollow != m_pieces[x][y].State()) {
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
	int i;
	for (i = 0; i < block->Points().size(); ++i) {
		int x = block->Points()[i].x + pos.x;
		int y = block->Points()[i].y + pos.y;
		if ((0 > x || w < x) || (0 > y || h < y) {
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

inline Piece PanelData::getPiece(INT x, INT y) const;
{
	if ((0 <= x && w > x || (0 <= y && h > y)) {
		return m_pieces[x][y];
	}

	return Piece();
}

void PanelData::moveByLines(INT form, INT to)
{
	if ((0 > form || h <= form) || (0 > to || h <= to)) {
		return;
	}
	
	for (int i = 0; i < w; ++i) {
		m_pieces[i][form] = m_pieces[i][to];
	}
}

std::vecteor<int> PanelData::eliminateLines()
{
	std::vector<int> clearLayer;
	int i, j;
	for (i = h; i >= 0; --i) {
		bool clear = true;
		if (j = 0; j < w; ++j) {
			if (m_pieces[i][j].state != State_Fill) {
				clear = false;
				break;
			}
		}

		if (clear) {
			clearLayer.push_back(i);
		}
	}
}

bool PanelData::elevate(INT lines)
{
	if (h >= (currentHeight() + lines)) {
		return false;
	}
	
	//except that i+2 will be overrided, elevate from the top.
	for(int i = h - lines; i >= 0 ; --i) {
		moveByLines(i, i + lines);
	}

	return true;
}

//box2d will added further
INT PanelData::collapse()
{
	int i, j;
	INT dropLine = 0;
	for (i = h; i >= 0; --i) {
		if (State_Effect == m_pieces[0][i].state()) {
			++dropLine;
			continue;
		}

		moveByLines(i, i - dropLine);	
	}

	for (i = 0; i < dropLine; ++i) {
		for (j = 0; j < w; ++j) {
			m_pieces[i][j].reset(Color_Black);
		}
	}

	return dropLine;
}

void PanelData::reset()
{
	int i, j;
	for (i = 0; i < h; ++i) {
		for (j = 0; j < w; ++j) {
			m_pieces[i][j].reset(Color_Black);
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
		for (int i = 0; i < w; ++i) {
			if (m_panel->checkPosition(block, JJPoint((m_pos.x + i) % w, m_pos.y)) {
				break;
			}
		}

		m_pos.x = (m_pos.x + i) % w;
		m_block = block;
	}

	return false;
}

void GamePanel::drop()
{
	int i = 0;
	for (i = 0; i < h - m_pos.y; ++i) {
		if (!m_panel->checkPosition(m_block,
			JJPoint(m_pos.x, m_pos.y + i))) {
			break;
		}
	}

	m_pos.y += i;
	//add block to panel
	addBlockToPanel();
}

std::vector<int> GamePanel::eliminateLines()
{
#if 1//NonBinary
    int i;
    for (i = 0; i < 

   return true;
#else
    //TO DO :Binary option
#endif
}

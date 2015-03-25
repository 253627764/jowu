#include "TetrisBlock.h
#include "TetrisDef.h"

static const int CoordsTable[7][4][2] = {
    { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, -2 } },//stick
    { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },//Z
    { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },//S
    { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } },//L
    { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },//RL
    { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },//hill
    { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },//square
};

static const Color_Type ColorTable[7] = {
	Color_Red,
	Color_Orange,
	Color_Yellow,
	Color_Green,
	Color_Purple,
	Color_Pink,
	Color_Black
};
    
static const int MaxChangeTimes[7] = { 2, 2, 2, 4, 4, 4, 1 };

#define CREATE_BLOCK(name) \
	Block##name::Block##name() \
    : Block(Block_##name) \
{ \
	int i = 0; \
	for (; i < 4; ++i) { \
		m_pieces[i] = Piece::create(ColorTable[Block_Stick],\
		JJPoint(CoordsTable[Block_Stick][i][0], CoordsTable[Block_Stick][i][1]); \
	} \
} \
	
TetrisBlock::TetrisBlock(Block_Type shape, Color_Type color,
             unsigned int maxChangeTime, const std::vector<JJPoint>& lst)
	: m_shape(shape),
	m_color(color),
	m_maxChangeTime(maxChangeTime) {
    memset(m_bitData, 0, sizeof(int));
    for (int i = 0; i < lst.size(); ++i) {
        m_bitData[lst[i].x + 2] |=  1 << (lst[i].y + 2);
		Piece* piece = Piece::create(color, lst[i]);
		if (!piece) {
			printf("create piece failed!!\n");
		}

		m_pieces.push_back(piece);
    }
}

int* TetrisBlock::bitData()
{
    return m_bitData;
}

//aglortihm: clockwise(x1=y, y1=x) 
//anitclockwise(x1=-y, y1=x)
TetrisBlock* TetrisBlock::rotate(bool clockWise)
{
	for (int i = 0; i < m_pieces.size(); ++i) {
		m_pieces[i]->setOffset(m_pieces[i]->offset().x,
			(clockWise? 1 : -1) * m_pieces[i]->offset().y);
	}

	return this;
}

bool TetrisBlock::locate(int x, int y)
{
	for (int i = 0; i < m_pieces.size(); ++i) {
		CCLog("piece %x x,y: %d , %d", m_pieces[i],  m_pieces[i]->offset().x + x, m_pieces[i]->offset().y + y);

		m_pieces[i]->setPosition(PIX * (m_pieces[i]->offset().x + x),
			PIX * (m_pieces[i]->offset().y + y));
		m_pieces[i]->setScale(0.2);
	}

	return true;
}

bool Block::rotate(bool clockwise)
{
	if (4 != m_pieces.size()) return false;
	for (int i = 0; i < 4; ++i) {
		if (m_pieces[i]) {
			m_pieces[i]->setPosition(m_pieces[i]->getPosition().y, (clockwise ? 1 : -1) * m_pieces[i]->getPosition().x);
		}
		else {
			return false;
		}
	}

	return  true;
}

void TetrisBlock::locate(float x, float y)
{
	for (int i = 0; i < m_pieces.size(); ++i) {
		CCLog("piece %x x,y: %d , %d", m_pieces[i],  m_pieces[i]->offset().x + x, m_pieces[i]->offset().y + y);

		m_pieces[i]->setPosition(PIX * (m_pieces[i]->offset().x + x),
			PIX * (m_pieces[i]->offset().y + y));
		m_pieces[i]->setScale(0.2);
	}
}

Block::Block(Block_Type type)
{
	m_type = type;
	m_maxChangeTime = MaxChangeTimes[type];
}

CREATE_BLOCK(stick);
CREATE_BLOCK(Z);
CREATE_BLOCK(S);
CREATE_BLOCK(L);
CREATE_BLOCK(MirrorL);
CREATE_BLOCK(Hill);
CREATE_BLOCK(Square);

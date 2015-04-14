#include "TetrisBlock.h"
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
    : Block(Block_##name, ColorTable[Block_##name]) \
{ \
	int i = 0; \
	for (; i < 4; ++i) { \
	    Piece* piece = Piece::create(ColorTable[Block_##name],\
		JJPoint(CoordsTable[Block_##name][i][0], CoordsTable[Block_##name][i][1])); \
		m_pieces.push_back(piece); \
	} \
} \

Block::~Block() 
{
}

bool Block::rotate(bool clockwise, const JJPoint& stub)
{
	for (int i = 0; i < 4; ++i) {
		m_hash |=  (1 << (2 - m_pieces[i]->offset().x)) << (4 * (1 - m_pieces[i]->offset().y));
	}
	for (int i = 0; i < 4; ++i) {
		m_pieces[i]->setOffset((clockwise ? 1 : -1) * m_pieces[i]->offset().y, 
		(clockwise ? -1 : 1) * m_pieces[i]->offset().x);
		m_pieces[i]->setPosition(PIX *(stub.x + m_pieces[i]->offset().x), 
			PIX * (stub.y + m_pieces[i]->offset().y));
	}

	return  true;
}

void Block::removeAllPiece()
{
	for (int i = 0; i < m_pieces.size(); ++i) {
		m_pieces[i]->removeFromParentAndCleanup(true);
	}
}

void Block::setPosition(float x, float y)
{
	for (int i =0 ;i < 4; ++i) {
		m_pieces[i]->updatePosition(x, y);
	}
}

Block::Block(Block_Type type, Color_Type color)
	:
	m_type(type),
	m_color(color),
	m_maxChangeTime(MaxChangeTimes[type]), 
	m_hash(0)
{
	
}

void Block::update(float delat)
{
	for (int i = 0; i < m_pieces.size(); ++i) {
		if (m_pieces[i]) {
			m_pieces[i]->update(delat);
		}
	}
}

CREATE_BLOCK(Stick);
CREATE_BLOCK(Z);
CREATE_BLOCK(S);
CREATE_BLOCK(L);
CREATE_BLOCK(MirrorL);
CREATE_BLOCK(Hill);
CREATE_BLOCK(Square);

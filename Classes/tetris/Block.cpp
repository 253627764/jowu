#include "Block.h"
namespace jowu {
Block::Block(TetrisBlock_Type shape, TetrisColor_Type color, 
	unsigned int maxChangeTime, unsigned int changedTime)
	: m_shape(shape),
	m_color(color),
	m_maxChangeTime(maxChangeTime),
	m_changedTime(changedTime) {}
	
void Block::rotate(bool clockwise)
{
	if (0 == m_units.size()) {
		return;
	}
	//TO DO
    
    
    std::vector<Point>::const_iterator iter = m_units.begin();
    for (; iter != m_units.end(); ++iter) {
        
    }

}

std::vector<int> Block::bitData();
{

}

ZBlock::ZBlock(TetrisBlock_Type )
{
	return TetrisBlock_Z;
}

virtual void rotate(bool clockwise)
{

}

virtual std::vector<int> bitData();
virtual unsigned int maxChangeTime();
virtual unsigned int changedTime();
virtual Point position();
virtual TetrisColor_Type color();
};






static const int coordsTable[8][4][2] = {
    { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },
    { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },
    { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },
    { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },
    { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },
    { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },
    { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },
    { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } }
};




class StickBlock : public Block
{
    StickBlock();
};

class ZBlock : public Block
{
    ZBlock();
};

class SBlock : public Block
{
    SBlock();
};

class LBlock : public Block
{
    LBlock();
};

class MirrorLBlock : public Block
{
    MirrorLBlock();
};

class HillBlock : public Block
{
    HillBlock();
};

class SquareBlock : public Block
{
    SquareBlock();
};



}
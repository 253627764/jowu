#include "Block.h"
namespace jowu {
Block::Block(TetrisBlock_Type shape, TetrisColor_Type color, 
	unsigned int maxChangeTime, unsigned int changedTime)
	: m_shape(shape),
	m_color(color),
	m_maxChangeTime(maxChangeTime),
	m_changedTime(changedTime) {}
	
void Block::clone(const Block& rhs)
{
	if (&rhs == this) {
		return;
	}

	rhs.m_shape = m_shape;
	rhs.m_color = m_color;
	rhs.m_maxChangeTime = m_maxChangeTime;
	rhs.m_changedTime = m_changedTime;

	rhs.Units().clear();
	std::copy(m_units.begin(), m_units.end(), std::back_inserter(rhs.Units()));

	m_left = rhs.left;
	m_right = rhs.right;
}

virtual void Block::rotate(bool clockwise)
{
	if (0 == m_units.size()) {
		return;
	}
	//TO DO

}
virtual Block::std::vector<int> bitData();
{

}

virtual ZBlock::ZBlock(TetrisBlock_Type )
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

}
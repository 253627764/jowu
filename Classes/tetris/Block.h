#ifndef JOWU_TETRIS_BLOCK
#define JOWU_TETRIS_BLOCK

#include "TetrisDef.h"
#include <cocos2d.h>
#include <vector>

namespace jowu 
{
class Unit
{
	JJ_PROPERTY(unsigned int, m_x, X);
	JJ_PROPERTY(unsigned int, m_y, Y);
	JJ_PROPERTY(unsigned int, m_state, Y);
	JJ_PROPERTY(unsigned int, m_color, Color);
	//考虑颜色融合、画布控制，预留渲染数据
public:
	Unit();
	Unit(const Unit&);
	Unit& operator=(const Unit&);
	~Unit();
};

class Block
{
	JJ_DISCPY(Block);
public:
	Block(TetrisBlock_Type shape, TetrisColor_Type color, unsigned int maxChangeTime, unsigned int changedTime);
	
	void clone(const Block& rhs);

	virtual void rotate(bool clockwise);
	std::vector<int> bitData();

	TetrisBlock_Type type() const { return m_shape; }
	TetrisColor_Type color() const { return m_color; }
	unsigned int maxChangeTime() const { return m_maxChangeTime; }
	unsigned int changedTime() const { return m_changedTime; }

	std::vector<Unit> Units() const { return m_units; }

	virtual unsigned int wieght() const { return 0; }

protected:
	std::vector<Unit> m_units;

private:
	TetrisBlock_Type m_shape;
	TetrisColor_Type m_color;
	unsigned int m_maxChangeTime;
	unsigned int m_changedTime;
	Block* m_left;
	Block* m_right;
};

class StickBlock : public Block
{

};

	TetrisBlock_Z,
	TetrisBlock_S,
	TetrisBlock_L,
	TetrisBlock_MirrorL,
	TetrisBlock_Hill,
	TetriBlock_Square,

class ZBlock : public Block
{

};

class SBlock : public Block
{
};

class LBlock : public Block
{
};

class MirrorLBlock : public Block
{
};

class HillBlock : public Block
{
};

class SquareBlock : public Block
{
};

#endif //JOWU_TETRIS_BLOCK
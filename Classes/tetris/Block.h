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

public:
	Unit();
	Unit(const Unit&);
	Unit& operator=(const Unit&);
	~Unit();
};
2
class Block
{
	JJ_DISCPY(Block);
public:
	Block(TetrisBlock_Type shape, TetrisColor_Type color, unsigned int maxChangeTime, unsigned int changedTime);
	
    virtual void create() = 0;
	virtual void rotate(bool clockwise);
	std::vector<int> bitData();

	TetrisBlock_Type type() const { return m_shape; }
	TetrisColor_Type color() const { return m_color; }
	unsigned int maxChangeTime() const { return m_maxChangeTime; }
	unsigned int changedTime() const { return m_changedTime; }


    Block* left() const { return m_left; }
    Block* right() const { return m_right; }
    std::vector<Point> Units() const { return m_units; }

	virtual unsigned int wieght() const { return 0; }

protected:
	std::vector<Point> m_units;

private:
	TetrisBlock_Type m_shape;
	TetrisColor_Type m_color;
	unsigned int m_maxChangeTime;
	unsigned int m_changedTime;
	Block* m_left;
	Block* m_right;
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

#endif //JOWU_TETRIS_BLOCK
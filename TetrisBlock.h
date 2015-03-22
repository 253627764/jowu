#ifndef JOWU_TETRIS_BLOCK
#define JOWU_TETRIS_BLOCK

#include "TetrisDef.h"
#include <cocos2d.h>
#include <vector>
#include "Piece.h"

#include "TetrisDef.h"

NS_USING_CC;


class Block : public Sprite
{
public:
	static Block* create();

	Block_Type type() const { return m_type; }
	int maxChangeTime() const { return m_maxChangeTime; }
	virtual void rotate();
	
private:
	Block_Type m_type;
	int m_maxChangeTime;
	Piece m_pieces[4];
};

class BlockStick : public Block
{
public:
	BlockStick* create();
};


enum Block_Type
{
	Block_Stick = 0,
	Block_Z,
	Block_S,
	Block_L,
	Block_MirrorL,
	Block_Hill,
	Block_Square,
	Block_Invalid,
	Block_Num = Block_Invalid
};

class BlockZ : public Block
{
public:
	BlockZ* create();
};


class BlockS : public Block
{
public:
	BlockS* create();
};


class BlockL : public Block
{
public:
	BlockL* create();
};


class BlockMirrorL : public Block
{
public:
	BlockMirrorL* create();
};


class BlockHill : public Block
{
public:
	BlockHill* create();
};

class BlockSquare : public Block
{
public:
	BlockSquare* create();
};



	



/*
class TetrisBlock : public Sprite
{
	JJ_DISCPY(TetrisBlock)
    friend class BlockGroup;
public:
    TetrisBlock(Block_Type shape, Color_Type color, unsigned int maxChangeTime, const std::vector<JJPoint>& lst);
	
	int* bitData();

	Block_Type type() const { return m_shape; }
	Color_Type color() const { return m_color; }
	unsigned int maxChangeTime() const { return m_maxChangeTime; }

    std::vector<Piece*> pieces() const { return m_pieces; }
	Piece* onePiece(unsigned int index) const { return m_pieces[index]; }
	virtual unsigned int wieght() const { return 0; }

	TetrisBlock* rotate(bool clockWise);
	//sync position with sprite
	bool locate(int x, int y);

private:
	Block_Type m_shape;
	Color_Type m_color;
	unsigned int m_maxChangeTime;
    std::vector<Piece*> m_pieces;
    int m_bitData[4];
};*/
#endif //JOWU_TETRIS_BLOCK

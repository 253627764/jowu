#ifndef JOWU_TETRIS_BLOCK
#define JOWU_TETRIS_BLOCK

#include "TetrisDef.h"
#include <cocos2d.h>
#include <vector>
#include "Piece.h"

#include "TetrisDef.h"

USING_NS_CC;

class Block : public Sprite
{
public:
	Block(Block_Type type);
	virtual ~Block();
	Block_Type type() const { return m_type; }
	int maxChangeTime() const { return m_maxChangeTime; }
	std::vector<Piece*> pieces() const { return m_pieces; }
	void removeAllPiece();

	virtual bool rotate(bool, const JJPoint&);
	void setPosition(float x, float y);
	void update(float delta);

private:
	Block_Type m_type;
	int m_maxChangeTime;

protected:
	std::vector<Piece*> m_pieces;
	int m_hash;
	
};

class BlockStick : public Block
{
public:
	BlockStick();
};

class BlockZ : public Block
{
public:
	BlockZ();
};


class BlockS : public Block
{
public:
	BlockS();
};

class BlockL : public Block
{
public:
	BlockL();
};

class BlockMirrorL : public Block
{
public:
	BlockMirrorL();
};

class BlockHill : public Block
{
public:
	BlockHill();
};

class BlockSquare : public Block
{
public:
	BlockSquare();
};

#endif //JOWU_TETRIS_BLOCK

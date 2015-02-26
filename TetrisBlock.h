#ifndef JOWU_TETRIS_BLOCK
#define JOWU_TETRIS_BLOCK

#include "TetrisDef.h"
#include <cocos2d.h>
#include <vector>
#include "Piece.h"

class TetrisBlock
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
	bool locate(float x, float y);

private:
	Block_Type m_shape;
	Color_Type m_color;
	unsigned int m_maxChangeTime;
    std::vector<Piece*> m_pieces;
    int m_bitData[4];
};
#endif //JOWU_TETRIS_BLOCK

#ifndef JOWU_TETRIS_BLOCK
#define JOWU_TETRIS_BLOCK

#include "TetrisDef.h"
#include <cocos2d.h>
#include <vector>

class TetrisBlock
{
    friend class BlockGroup;
	JJ_DISCPY(TetrisBlock)
public:
    TetrisBlock(TetrisBlock_Type shape, TetrisColor_Type color,
                unsigned int maxChangeTime, unsigned int changedTime, const std::vector<JJPoint>& lst);
	
	int* bitData();

	TetrisBlock_Type type() const { return m_shape; }
	TetrisColor_Type color() const { return m_color; }
	unsigned int maxChangeTime() const { return m_maxChangeTime; }
	unsigned int changedTime() const { return m_changedTime; }


    TetrisBlock* left() const { return m_left; }
    TetrisBlock* right() const { return m_right; }
    std::vector<JJPoint> Points() const { return m_points; }

	virtual unsigned int wieght() const { return 0; }

protected:
	std::vector<JJPoint> m_points;

private:
    void setLeft(TetrisBlock* b) { m_left = b; }
    void setRight(TetrisBlock*　b) { m_right = b; }
    
	TetrisBlock_Type m_shape;
	TetrisColor_Type m_color;
	unsigned int m_maxChangeTime;
	unsigned int m_changedTime;
	TetrisBlock* m_left;
	TetrisBlock* m_right;
    int m_bitData[4];
};

class BlockGroup
{
    JJ_DISCPY(BlockGroup)
public:
    BlockGroup();
    //static BlockGroup* instance();
private:
    bool addBlockToGroup(TetrisBlock_Type shape, TetrisColor_Type color, unsigned int maxChangeTime, const std::vector<JJPoint>& lst);
    void initialize();

    bool rotate(std::vector<JJPoint>& lstOut);
private:
    //static BlockGroup* s_instance;
private:
    std::vector<TetrisBlock*> m_blocks;
};
#endif //JOWU_TETRIS_BLOCK

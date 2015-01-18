#include "TetrisBlock.h"
TetrisBlock::TetrisBlock(TetrisBlock_Type shape, TetrisColor_Type color,
             unsigned int maxChangeTime, unsigned int changedTime, const std::vector<JJPoint>& lst)
	: m_shape(shape),
	m_color(color),
	m_maxChangeTime(maxChangeTime),
	m_changedTime(changedTime),
    m_left(this),
    m_right(this) {
    memset(m_bitData, 0, 4);
    for (int i = 0; i < lst.size(); ++i) {
        m_bitData[lst[i].x + 2] |=  1 << (lst[i].y + 2);
    }
}

int* TetrisBlock::bitData()
{
    return m_bitData;
}

BlockGroup::BlockGroup()
{
    initialize();
}

//rotate clockwise
std::vector<JJPoint> BlockGroup::rotate(const std::vector<JJPoint>& lst)
{
    int i;
    std::vector<JJPoint> ret;
    for (i = 0; i < 4; ++i) {
        ret.push_back(JJPoint(lst[i].y, -lst[i].x));
    }
    
    return ret;
}

void BlockGroup::addBlockToGroup(TetrisBlock_Type shape, TetrisColor_Type color,
                            unsigned int maxChangeTime,const std::vector<JJPoint>& lst)
{
    int i;
    TetrisBlock* block = new TetrisBlock(shape, color, maxChangeTime, 0, lst);
    m_blocks.push_back(block);
    TetrisBlock* pre = block;
    TetrisBlock* cur;
    for (i = 1; i < maxChangeTime; ++i) {
        cur = new TetrisBlock(shape, color, maxChangeTime, i, lst);//rotate(lst));
        cur->setLeft(pre);
        pre->setRight(cur);
        pre = cur;
    }
    
    if (1 <= maxChangeTime) {
        block->setLeft(cur);
        cur->setRight(block);
    }
}

void BlockGroup::initialize()
{
    static const int coordsTable[7][4][2] = {
        { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },//stick
        { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },//Z
        { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },//S
        { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } },//L
        { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },//RL
        { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },//hill
        { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },//square
    };
    
    static const int maxChangeTimes[7] = {
    
    if (!m_blocks.empty()) {
        m_blocks.clear();
    }
    
    int i, j;
    for (i = 0; i < 7; ++i) {
        std::vector<JJPoint> lst;
        for (j = 0; j < 4; ++j) {
            lst.push_back(JJPoint(coordsTable[i][j][0], coordsTable[i][j][1]));
        }

        addBlockToGroup((TetrisBlock_Type)i, TetrisColor_Black, 2, lst);
    }
    
    int a = 0;
}
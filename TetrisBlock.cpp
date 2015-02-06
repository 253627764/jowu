#include "TetrisBlock.h"
TetrisBlock::TetrisBlock(Block_Type shape, Color_Type color,
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

        m_points.push_back(JJPoint(lst[i].x, lst[i].y));
    }
}

int* TetrisBlock::bitData()
{
    return m_bitData;
}

BlockGroup::BlockGroup()
{
    printf("BlockGroup::BlockGroup\n");
    initialize();
}

//rotate clockwise
bool BlockGroup::rotate(std::vector<JJPoint>& lstOut)
{
    if (4 != lstOut.size()) {
        printf("BlockGroup::rotate size error\n");
        return false;
    }
    
    int i;
    std::vector<JJPoint> ret;
    for (i = 0; i < 4; ++i) {
        int tmpX = lstOut[i].x;
        lstOut[i].x = lstOut[i].y;
        lstOut[i].y = tmpX;
    }
    
    return true;
}

bool BlockGroup::addBlockToGroup(Block_Type shape, Color_Type color,
                            unsigned int maxChangeTime, const std::vector<JJPoint>& lst)
{
    int i;
    TetrisBlock* block = new TetrisBlock(shape, color, maxChangeTime, 0, lst);
    if (!block) {
        //JJLOGE("alocate memory failed !");
        return false;
    }
    m_blocks.push_back(block);
    TetrisBlock* pre = block;
    TetrisBlock* cur;
    std::vector<JJPoint> lstRotate(lst);
    for (i = 1; i < maxChangeTime; ++i) {
        rotate(lstRotate);
        cur = new TetrisBlock(shape, color, maxChangeTime, i, lstRotate);//rotate(lst));
        cur->setLeft(pre);
        pre->setRight(cur);
        pre = cur;
    }
    
    if (1 < maxChangeTime) {
        block->setLeft(cur);
        cur->setRight(block);
    }
    
    return true;
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
    
    static const int maxChangeTimes[7] = { 2, 2, 2, 4, 4, 4, 1 };
    
    if (!m_blocks.empty()) {
        m_blocks.clear();
    }
    
    int i, j;
    for (i = 0; i < 7; ++i) {
        std::vector<JJPoint> lst;
        for (j = 0; j < 4; ++j) {
            lst.push_back(JJPoint(coordsTable[i][j][0], coordsTable[i][j][1]));
        }

        addBlockToGroup((Block_Type)i, Color_Black, maxChangeTimes[i], lst);
    }
}

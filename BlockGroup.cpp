#include "BlockGroup.h"

BlockGroup::BlockGroup()
{
    printf("BlockGroup::BlockGroup\n");
    initialize();
}

bool BlockGroup::addBlockToGroup(Block_Type shape, Color_Type color,
                            unsigned int maxChangeTime, const std::vector<JJPoint>& lst)
{
    TetrisBlock* block = new TetrisBlock(shape, color, maxChangeTime, lst);
    if (!block) {
        //JJLOGE("alocate memory failed !");
        return false;
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

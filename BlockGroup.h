#include "TetrisDef.h"
#include "TetrisBlock.h"
#include <vector>

class BlockGroup
{
    JJ_DISCPY(BlockGroup)
public:
    BlockGroup();
    TetrisBlock* getBlock();
    
    static BlockGroup* instance();
private:
    bool addBlockToGroup(Block_Type shape, Color_Type color, unsigned int maxChangeTime, const std::vector<JJPoint>& lst);
    void initialize();

    bool rotate(std::vector<JJPoint>& lstOut);
private:
    static BlockGroup* s_instance;
private:
    std::vector<TetrisBlock*> m_blocks;
};
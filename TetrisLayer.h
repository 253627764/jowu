#ifndef TETRISLAYER_H
#define TETRISLAYER_H
#include "TetrisDef.h"
#include "TetrisBlock.h"
#include "GamePanel.h"

#define PanelWidth 12
#define PanelHeight 24
static const int NextNum = 3;

class TetrisLayer
{
    JJ_DISCPY(TetrisLayer)
    unsigned int m_speed;
    JJPoint m_pos;
    TetrisBlock* m_block;
    TetrisBlock m_nextBlocks[NextNum];
    GamePanel* m_panel;
public:
    TetrisLayer();

    bool addBlockToPanel(TetrisBlock *block, const JJPoint &pos);
    bool down();
    bool moveLeft();
    bool moveRight();
    bool rotate(bool clockWise);
    void drop();
    unsigned int eliminateLines();

    //effect interface to do
    void eggShell() {}
private:
    bool checkPosition(TetrisBlock* block, const JJPoint& pos);

};



#endif // TETRISLAYER_H

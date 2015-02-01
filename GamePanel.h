#ifndef GAMEPANEL_H
#define GAMEPANEL_H
#include "TetrisDef.h"
#include "TetrisBlock.h"

#define PanelInst GetPanelInstance();

#define PanelWidth 12
#define PanelHeight 24
static const int NextNum = 3;
class PanelData;
class GamePanel
{
    JJ_DISCPY(GamePanel)
    unsigned int m_speed;
    JJPoint m_pos;
    TetrisBlock* m_block;
    TetrisBlock m_nextBlocks[NextNum];
    PanelData* m_panel;
public:
    GamePanel();

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



#endif

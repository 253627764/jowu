#ifndef TETRIS_LAYGER_H
#define TETRIS_LAYGER_H

#include "cocos2d.h"



#include "GamePanel.h"
#include "TetrisDef.h"
#include "TetrisBlock.h"

#define PanelInst GetPanelInstance();

#define PanelWidth 12
#define PanelHeight 24
static const int NextNum = 3;

class TetrisLayer : public cocos2d::Layer
{
    int m_x;
    int m_y;
};

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

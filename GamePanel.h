#ifndef GAMEPANEL_H
#define GAMEPANEL_H
#include "TetrisDef.h"
#include "TetrisBlock.h"

class GamePanel
{
    JJ_DISCPY(GamePanel)
    unsigned int m_width;
    unsigned int m_height;
    TetrisBlock* m_block;
public:
    GamePanel();
    
private:
    bool moveLeft();
    bool moveRight();
    bool rotateLeft();
    bool rotateRight();
    //bool hasten();
    bool drop();
    //bool tryMove();
    bool tryRotate();
    unsigned int eliminateLines();
    
};

#endif
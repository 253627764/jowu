#ifndef GAMEPANEL_H
#define GAMEPANEL_H
#include "TetrisDef.h"
#include "TetrisBlock.h"

static const int PanelWidth = 12;
static const int PanelHeight = 24;

class Piece
{
    JJ_DISCPY(Piece)
public:
    Piece(unsigned int x, unsigned int y, int state, TetrisColor_Type color)
        : m_x(x), m_y(y), m_state(state), m_color(color) {}
    virtual ~Piece() {}
    unsigned int X() const { return m_x; }
    unsigned int Y() const { return m_y; }
    int State() const { return m_state; }
    TetrisColor_Type color() const { return m_color; }
private:
    int m_state;//0 null 1 block
    unsigned int m_x;
    unsigned int m_y;
    TetrisColor_Type m_color;
};

class PanelData
{
    PanelData(unsigned int width = PanelWidth,
              unsigned int height PanelHeight);
    virtual ~PanelData() {}
    static PanelData* instance();
    
    inline
    
private:
    static PanelData* s_instance;
private:
    std::vector<unsigned int> m_data;
    PanelData m_pieceArray[PanelWidth][PanelHeight];
};

class GamePanel
{
    JJ_DISCPY(GamePanel)
    
    TetrisBlock* m_block;
public:
    GamePanel();
    
    
    bool addBlockToPanel(TetrisBlock *block, const JJ_Point &pos);
    bool down();
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
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
    
    GamePanel* m_panel;
public:
    TetrisLayer();

    bool addBlockToPanel(TetrisBlock *block, const JJPoint &pos);
    bool down();
    bool moveLeft();
    bool moveRight();
    bool rotate(bool clockWise);
    bool drop();

	TetrisBlock* block();
	JJPoint position();
	unsigned int speed();

	//effect interface to do
    void eggShell() {}
private:
    bool checkPosition(TetrisBlock* block, const JJPoint& pos);

};
#endif // TETRISLAYER_H

#ifndef TETRISLAYER_H
#define TETRISLAYER_H
#include "TetrisDef.h"
#include "TetrisBlock.h"
#include "GamePanel.h"

#define PanelWidth 12
#define PanelHeight 24

class TetrisLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(TetrisLayer);
	~TetrisLayer();

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
	GamePanel *m_panel;

};
#endif // TETRISLAYER_H

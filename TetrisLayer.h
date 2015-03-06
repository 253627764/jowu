#ifndef TETRISLAYER_H
#define TETRISLAYER_H
#include "TetrisDef.h"
#include "TetrisBlock.h"
#include "GamePanel.h"
USING_NS_CC;

#define PanelWidth 12
#define PanelHeight 24

class TetrisLayer : public Layer
{
public:
	virtual bool init();
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void update(float delat);


	CREATE_FUNC(TetrisLayer);
	void runThisTest();
private:
	GamePanel *m_panel;

};
#endif // TETRISLAYER_H

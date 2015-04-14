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
	virtual void update(float delta);
	
	CREATE_FUNC(TetrisLayer);
	void runThisTest();
	void tick(float delta);

	static void loadResource();
	void gameOver();
	GamePanel* getPanel() const { return m_panel; }
private:
	CCSprite* jj;
	GamePanel *m_panel;
};
#endif // TETRISLAYER_H

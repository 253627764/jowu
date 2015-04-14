#ifndef GAMEPANEL_H
#define GAMEPANEL_H
#include "TetrisDef.h"
#include "TetrisBlock.h"
#include "AI/SmartController.h"

#include "cocos2d.h"
using namespace cocos2d;

#define PanelInst GetPanelInstance();

#define PanelWidth 12
#define PanelHeight 24
static const int NextNum = 3;

class GamePanel : public Node
{
public:
	GamePanel();
	static GamePanel* create();
	bool init();
	void updatePiece(float delat);
	
	bool checkPosition(Block* block, const JJPoint& pos);
	bool addBlockToPanel(Block* block, const JJPoint &pos);
	
	std::vector<int> eliminateLines();
	unsigned int collapse();
	
	unsigned int speed() const { return m_speed; }
	void setSpeed(unsigned int speed) { m_speed = speed; }

	Block* block() const { return m_block; }
	void setBlock(Block* block) { m_block = block; }

	JJPoint position() const { return m_pos; }
	
	unsigned int currentHeight() const;
    bool elevate(unsigned int lines);
    void reset();
	bool down();
	bool moveLeft();
	bool moveRight();
	bool rotate(bool clockWise);
	bool drop();
    
	void reStart();
    void tick(float delta);
	void update(float delta);

	std::function<void(void)> gameOverCallback;

private:
	void moveByLines(unsigned int form, unsigned int to);
    void getRandomBlock();
	void adjustPieces();
	void debug();
private:
	Vec2 m_origin;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_speed; // not handle yet
	int m_data[PanelHeight];
	Block* m_block;
    std::list<Block*> m_nextBlocks;
	JJPoint m_pos;
	int m_state[PanelWidth][PanelHeight];
    Piece* m_pieces[PanelWidth][PanelHeight];
	bool gameOver;
	//SmartController* m_controller;
};
#endif

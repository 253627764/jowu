#ifndef GAMEPANEL_H
#define GAMEPANEL_H
#include "TetrisDef.h"
#include "TetrisBlock.h"
#include "cocos2d.h"
using namespace cocos2d;

#define PanelInst GetPanelInstance();

#define PanelWidth 12
#define PanelHeight 24
static const int NextNum = 3;

class GamePanel : public Node
{
public:
	static GamePanel* create();
	bool init();
	void updatePiece(float delat);
	
	bool checkPosition(TetrisBlock* block, const JJPoint& pos);
	bool addBlockToPanel(TetrisBlock* block, const JJPoint &pos);
	
	std::vector<int> eliminateLines();
	unsigned int collapse();
	
	unsigned int speed() const { return m_speed; }
	void setSpeed(unsigned int speed) { m_speed = speed; }

	TetrisBlock* block() const { return m_block; }
	void setBlock(TetrisBlock* block) { m_block = block; }

	JJPoint position() const { return m_pos; }
	void setPosition(const JJPoint& pos) { m_pos = pos; }
	unsigned int currentHeight() const;
    bool elevate(unsigned int lines);
    void reset();
	bool down();
	bool moveLeft();
	bool moveRight();
	bool rotate(bool clockWise);
	bool drop();
    
    void tick(float delta);

private:
	void moveByLines(unsigned int form, unsigned int to);
    void getRandomBlock();

private:
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_speed; // not handle yet
    std::vector<unsigned int> m_data;
	TetrisBlock* m_block;
    std::list<TetrisBlock*> m_nextBlocks;
	JJPoint m_pos;
    Piece* m_pieces[PanelWidth][PanelHeight];
	
    
};
#endif

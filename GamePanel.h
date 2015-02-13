#ifndef GAMEPANEL_H
#define GAMEPANEL_H
#include "TetrisDef.h"
#include "TetrisBlock.h"

#define PanelInst GetPanelInstance();

#define PanelWidth 12
#define PanelHeight 24
static const int NextNum = 3;

class GamePanel
{
public:
    GamePanel(unsigned int width = PanelWidth, unsigned int height = PanelHeight);
    virtual ~GamePanel() {}
    static GamePanel* instance();
	//inline Piece getPiece(unsigned int x, unsigned int y) const;

    bool update(TetrisBlock* block, const JJPoint &pos);
	bool checkPosition(TetrisBlock* block, const JJPoint& pos);
	std::vector<int> eliminateLines();
	unsigned int collapse();
	void moveByLines(unsigned int form, unsigned int to);
	unsigned int currentHeight() const;
    bool elevate(unsigned int lines);
    void reset();

private:
    static GamePanel* s_instance;
private:
	unsigned int m_width;
	unsigned int m_height;
    std::vector<unsigned int> m_data;
    Piece **m_pieces;
};



#endif

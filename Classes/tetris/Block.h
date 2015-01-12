#ifndef JOWU_TETRIS_BLOCK
#define JOWU_TETRIS_BLOCK

#include "TetrisDef.h"
#include <cocos2d.h>
#include <vector>

namespace jowu 
{
class Unit
{
	JJ_PROPERTY(unsigned int, m_x, "X");
	JJ_PROPERTY(unsigned int, m_y, "Y");
	JJ_PROPERTY(unsigned int, m_state, "Y");
	JJ_PROPERTY(unsigned int, m_color, "Color");
	//考虑颜色融合、画布控制，预留渲染数据
public:
	Unit();
	Unit(const Unit&);
	Unit& operator=(const Unit&);
	~Unit();
};

class Block
{
	CC_SYNTHESIZE_READONLY(Block*, m_left, left);
	CC_SYNTHESIZE_READONLY(Block*, m_right, right);
public:
	Block();
	init();
	virtual void rotate(bool left) = 0;
private:
	std::vector<Unit> m_data;
};

class Stick : public Block
{

};

class 

}

#endif //JOWU_TETRIS_BLOCK
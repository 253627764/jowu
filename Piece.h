#ifndef PIECE_H
#define PIECE_H

#include "math\Vec2.h"
#include "TetrisDef.h"
#include "cocos2d.h"
class Piece : public cocos2d::Sprite
{
    JJ_DISCPY(Piece)
	friend class TetrisBlock;
public:
	Piece(State_Type state = State_Invalid, Color_Type color = Color_Invalid);
    virtual ~Piece() {}
	
	static Piece* create(Color_Type color, const JJPoint& pos);
	void init(Color_Type color);
	
	void copy(const Piece& rhs); // deep copy

	const JJPoint& offset() const { return m_offset; }
    State_Type State() const { return m_state; }
    Color_Type Color() const { return m_color; }

    void setState(const State_Type& state) { m_state = state; }
    void setColor(const Color_Type& color) { m_color = color; }
private:
	void setOffset(float x, float y);
	char* getImageByColor(Color_Type color);
private:
	JJPoint m_offset;//the offset to center postion
    State_Type m_state;//0 null 1 block
    Color_Type m_color;
};

#endif // PIECE_H

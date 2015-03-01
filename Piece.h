#ifndef PIECE_H
#define PIECE_H

//#include "math\Vec2.h"
#include "TetrisDef.h"
#include "cocos2d.h"

using namespace cocos2d;
class Piece : public Sprite
{
    JJ_DISCPY(Piece)
	friend class TetrisBlock;
public:
	Piece(State_Type state = State_Invalid, Color_Type color = Color_Invalid);
    virtual ~Piece() {}
	
	static Piece* create(Color_Type color, const JJPoint& pos);
	void init(Color_Type color);
	
	JJPoint destination() const { return m_destination; }
	const JJPoint& offset() const { return m_offset; }
    State_Type State() const { return m_state; }
    Color_Type Color() const { return m_color; }

	void setDestinationX(const float x) { m_destination.x = x; }
	void setDestinationY(const float y) { m_destination.y = y; }
	void setDestination(const JJPoint& pos) { m_destination = pos; }
    void setState(const State_Type& state) { m_state = state; }
    void setColor(const Color_Type& color) { m_color = color; }

private:
	void setOffset(float x, float y);
	char* getImageByColor(Color_Type color);

protected:
    JJPoint m_offset;//the offset to center postion

private:
	JJPoint m_destination;
	JJPoint m_pos;
    State_Type m_state;//0 null 1 block
    Color_Type m_color;
};

#endif // PIECE_H

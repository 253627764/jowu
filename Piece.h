#ifndef PIECE_H
#define PIECE_H

#include "math\Vec2.h"
#include "TetrisDef.h"
#include "cocos2d.h"
class Piece : public cocos2d::Sprite
{
    JJ_DISCPY(Piece)
public:
	Piece(State_Type state, Color_Type color);
    virtual ~Piece() {}
	
	static Piece* create(Color_Type color, const JJPoint& pos);
	void init(Color_Type color);
	
	const JJPoint& absPos() const { return m_absPos; }
    State_Type State() const { return m_state; }
    Color_Type Color() const { return m_color; }

	void setAbsPos(float x, float y);
	void setAbsPos(const JJPoint& pos);
    void setState(const State_Type& state) { m_state = state; }
    void setColor(const Color_Type& color) { m_color = color; }
private:
	char* getImageByColor(Color_Type color);
private:
	JJPoint m_absPos;
    State_Type m_state;//0 null 1 block
    Color_Type m_color;
};

#endif // PIECE_H

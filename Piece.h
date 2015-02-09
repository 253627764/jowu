#ifndef PIECE_H
#define PIECE_H

#include "TetrisDef.h"

class Piece : public cocos2d::Sprite
{
    JJ_DISCPY(Piece)
public:
    Piece(unsigned int x, unsigned int y, State_Type state,
        Color_Type color)
        : m_x(x), m_y(y), m_state(state), m_color(color) {}
    Piece()
        : m_x(-1), m_y(-1),
        m_state(State_Invalid), m_color(Color_Invalid) {}
    virtual ~Piece() {}

    inline void clone(const Piece& ref) {
        m_x = ref.X();
        m_y = ref.Y();
        m_state = ref.State();
        m_color = ref.Color();
    }

    inline void reset(Color_Type color) { m_x = -1; m_y = -1;
        m_state = State_Invalid; m_color = color; }

    unsigned int X() const { return m_x; }
    unsigned int Y() const { return m_y; }
    State_Type State() const { return m_state; }
    Color_Type Color() const { return m_color; }

    void setX(unsigned int x) { m_x = x; }
    void setY(unsigned int y) { m_y = y; }
    void setState(const State_Type& state) { m_state = state; }
    void setColor(const Color_Type& color) { m_color = color; }

private:
    State_Type m_state;//0 null 1 block
    unsigned int m_x;
    unsigned int m_y;
    Color_Type m_color;
};

#endif // PIECE_H

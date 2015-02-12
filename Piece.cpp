#include "Piece.h"

Piece::Piece(State_Type state = State_Invalid, Color_Type color = Color_Invalid)
	: m_state(state), m_color(color)
{
	memset(&m_absPos, -1, sizeof(JJPoint));
}

Piece* Piece::create(Color_Type color, const JJPoint& pos)
{
	Piece* ret = new Piece();
	if (ret && ret->initWithFile(ret->getImageByColor(color))){
		ret->setState(State_Fill);
		ret->setColor(color);
		ret->setAbsPosition(pos);
		ret->autorelease();
		return ret;
	}
	else {
		delete ret;
		ret = NULL;
		return NULL;
	}
}

void Piece::setAbsPos(float x, float y)
{
	m_absPos.x = x;
	m_absPos.y = y;
}

void Piece::setAbsPos(const JJPoint& pos)
{
	m_absPos.x = pos.x;
	m_absPos.y = pos.y;
}

char* Piece::getImageByColor(Color_Type color)
{
	switch (color) {
	case Color_Black:
		return "black.png";
	case Color_Red:
		return "red.png";
	case Color_Yellow:
		return "yellow.png";
	case Color_Green:
		return "green.png";	
	case Color_Cyan:
		return "cyan.png";
	case Color_Blue:
		return "blue.png";
	case Color_Purple:
		return "purple.png";
	case Color_Pink:
	    return "pink.png";
	default:
		return "black.png";
	}
}


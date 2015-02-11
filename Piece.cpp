#include "Piece.h"

Piece* Piece::create(Color_Type color)
{
	Piece* ret = new Piece();
	if (ret && ret->initWithFile(ret->getImageByColor(color))){
		ret->m_color = color;
		ret->autorelease();
		return ret;
	}
	else {
		delete ret;
		ret = NULL;
		return NULL;
	}
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


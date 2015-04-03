#include "Piece.h"


Piece::Piece(State_Type state, Color_Type color)
	: m_state(state),
	m_color(color)
{
}

Piece::~Piece()
{
	int debug =1;
	int debg = 2;
}

Piece* Piece::create(Color_Type color, const JJPoint& pos)
{
	Piece* ret = new Piece();
 	if (ret){
		Texture2D* texture = CCTextureCache::sharedTextureCache()->addImage(getImageByColor(color));
		ret->initWithTexture(texture);
		ret->setState(State_Hollow);
		ret->setColor(color);
		ret->setOffset(pos.x , pos.y);
		ret->setScale(0.2f);
		//ret->setContentSize(Size(20, 20));
		CCSize size = ret->getContentSize();
		ret->autorelease();
		return ret;
	}
	else {
		delete ret;
		ret = NULL;
		return NULL;
	}
}

Piece* Piece::create()
{
	Piece* ret = new Piece();
 	if (ret){
		Texture2D* texture = CCTextureCache::sharedTextureCache()->addImage("darkblue.png");
		ret->initWithTexture(texture);
		ret->setState(State_Hollow);
		
		ret->setScale(0.2);
		Size s = ret->getContentSize();
		ret->autorelease();
		return ret;
	}
	else {
		delete ret;
		ret = NULL;
		return NULL;
	}
}

void Piece::setOffset(float x, float y)
{
	m_offset.x = x;
	m_offset.y = y;
}

void Piece::updatePosition(float x, float y)
{
	setPosition(PIX * m_offset.x + x, PIX *m_offset.y + y);
}

std::string Piece::getImageByColor(Color_Type color)
{
	switch (color) {
	case Color_Black:
		return "purple.png";
	case Color_Red:
		return "red.png";
	case Color_Yellow:
		return "yellow.png";
	case Color_Green:
		return "green.png";	
	case Color_Orange:
		return "brown.png";// color adjust
	case Color_Blue:
		return "blue.png";
	case Color_Purple:
		return "purple.png";
	case Color_Pink:
	    return "pink.png";
	default:
		return "darkblue.png";
	}
}


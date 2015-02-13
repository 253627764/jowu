#ifndef TETRIS_DEF_H
#define TETRIS_DEF_H
#include <stdarg.h>

#define JJ_DISCPY(class) \
	class(const class&); \
	class& operator=(const class&);

//from CC_PROPERTY
//#define JJ_PROPERTY(varType, varName, funName)\
//private: varType varName;\
//public: varType get##funName(void);\
//public: void set##funName(varType var);

enum Color_Type
{
	Color_Black  = 0x00000000,
	Color_Red    = 0x00FF0000,
	Color_Orange = 0x00FFA500,//255,165,0
	Color_Yellow = 0x00FFFF00,
	Color_Green  = 0x00008000,//0,128,0
	Color_Cyan   = 0x0000FFFF,
	Color_Blue   = 0x000000FF,
	Color_Purple = 0x00800080,//128,0,128
	Color_Pink   = 0x00FFC0CB,//255,192,203
    Color_Num,
	Color_Invalid = Color_Num
};

enum Block_Type
{
	Block_Stick = 0,
	Block_Z,
	Block_S,
	Block_L,
	Block_MirrorL,
	Block_Hill,
	Block_Square,
	Block_Invalid,
	Block_Num = Block_Invalid
};

enum State_Type
{
	State_Hollow = 0,
	State_Fill,
	State_Effect,
	State_Invalid,
	State_Num = State_Invalid
};

class JJPoint
{
public:
    JJPoint(int _x = -1, int _y = -1)
    : x(_x), y(_y) {}
	JJPoint(const JJPoint& rhs)
		: x(rhs.x), y(rhs.y) {}
	JJPoint& operator= (const JJPoint& rhs)
	{
		x = rhs.x;
		y = rhs.y;
	}

	int x;
	int y;
};

#endif
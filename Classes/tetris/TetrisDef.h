#include <stdarg.h>

#define JJ_DISCPY(class) \
	class(const class&); \
	class& operator=(const class&);

//from CC_PROPERTY
#define JJ_PROPERTY(varType, varName, funName)\
private: varType varName;\
public: varType get##funName(void);\
public: void set##funName(varType var);

enum TetrisColor_Type
{
	TetrisColor_Black  = 0x00000000,
	TetrisColor_Red    = 0x00FF0000,
	TetrisColor_Orange = 0x00FFA500,//255,165,0
	TetrisColor_Yellow = 0x00FFFF00,
	TetrisColor_Green  = 0x00008000,//0,128,0
	TetrisColor_Cyan   = 0x0000FFFF,
	TetrisColor_Blue   = 0x000000FF,
	TetrisColor_Purple = 0x00800080,//128,0,128
	TetrisColor_Pink   = 0x00FFC0CB,//255,192,203
	TetrisColor_Num = 9
};

enum TetrisBlock_Type
{
	TetrisBlock_Stick = 0,
	TetrisBlock_Zshape,
	TetrisBlock_Zrshape,
	TetrisBlock_Lshape,
	TetrisBlock_Lrshape,
	TetrisBlock_Hill,
	TetriBlock_Square,
	TetriBlock_Invalid,
	TetriBlockNum = TetriBlock_Invalid
};
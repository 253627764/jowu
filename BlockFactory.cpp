#include "BlockFactory.h"
#include "TetrisBlock.h"


Block* BlockFactory::create(Block_Type type)
{
	switch (type) {
	case Block_Stick:
		{
			return new BlockStick;
		}
		break;
	case Block_S:
		{
			return new BlockS;
		}
		break;
	case Block_Z:
		{
			return new BlockZ;
		}
		break;
	case Block_L:
		{
			return new BlockL;
		}
		break;
	case Block_MirrorL:
		{
			return new BlockMirrorL;
		}
		break;
	case Block_Hill:
		{
			return new BlockHill;
		}
		break;
	case Block_Square:
		{
			return new BlockSquare;
		}
		break;
	default:
		{
			return nullptr;
		}
		break;
	}
}
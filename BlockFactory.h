#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H
#include "TetrisDef.h"

class Block;
class BlockFactory
{
public:
	static Block* create(Block_Type type);
};

#endif //BLOCKFACTORY_H
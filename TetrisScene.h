#ifndef TETRIS_SCENE_H
#define TETRIS_SCENE_H
#include "cocos2d.h"

class TetrisLayer;
class OperateLayer;
class TetrisScene : public cocos2d::Scene
{
public:
    virtual bool init();
    CREATE_FUNC(TetrisScene);
	
private:
	TetrisLayer* m_gameLayer;
	OperateLayer* m_operateLayer;
};

#endif
#ifndef TETRIS_SCENE_H
#define TETRIS_SCENE_H
#include "cocos2d.h"

class TetrisScene : public cocos2d::Scene
{
public:
    virtual bool init();
    CREATE_FUNC(TetrisScene);
};

#endif
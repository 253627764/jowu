#ifndef _Progress_H_
#define _Progress_H_
 
#include "cocos2d.h"
USING_NS_CC;
 
class Progress : public CCLayer
{
public:
    static CCScene* scene();
 
    bool init();
 
    CREATE_FUNC(Progress);
 
    void scheduleFunc(float dt);
};
 
#endif
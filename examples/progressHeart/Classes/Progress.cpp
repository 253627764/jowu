#include "Progress.h"
//#include "pr
 
CCScene* Progress::scene()
{
    CCScene* scene = CCScene::create();
 
    Progress* layer = Progress::create();
 
    scene->addChild(layer);
 
    return scene;
}
 
bool Progress::init()
{
    CCLayer::init();
 
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
 
    CCPoint center = ccp(winSize.width / 2, winSize.height / 2);
 
    CCSprite* bg = CCSprite::create("2.png");
    CCSprite* sprite = CCSprite::create("1.png");
 
    bg->setPosition(center);
 
    addChild(bg);
 
    CCProgressTimer* progress = CCProgressTimer::create(sprite);
 
    progress->setPosition(center);
 
    addChild(progress);
 
    //设置进度条的模式
    //kCCProgressTimerTypeBar表示条形模式
    progress->setType(kCCProgressTimerTypeBar);
 
    //设置进度条变化的方向
    //ccp(0,1)表示沿着y轴变化
    progress->setBarChangeRate(ccp(0,1));
 
    //设置进度条的起始位置
    //ccp(0,0)表示下面
    progress->setMidpoint(ccp(0,0));
 
    //设置进度条的ID
    progress->setTag(100);
 
    //创建一个定时器
    schedule(schedule_selector(Progress::scheduleFunc), 0.1f);
 
    return true;
}
 
void Progress::scheduleFunc(float dt)
{
    //通过进度条的ID得到进度条
    CCProgressTimer* progress = (CCProgressTimer*)getChildByTag(100);
 
   //设置progress的进度，每调用一次进度加一
    progress->setPercentage(progress->getPercentage() + 1);
     
     //当进度大于或者等于100时
    if(progress->getPercentage() >= 100)
    {
          //终止定时器
        unscheduleAllSelectors();
    }
}
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
 
    //���ý�������ģʽ
    //kCCProgressTimerTypeBar��ʾ����ģʽ
    progress->setType(kCCProgressTimerTypeBar);
 
    //���ý������仯�ķ���
    //ccp(0,1)��ʾ����y��仯
    progress->setBarChangeRate(ccp(0,1));
 
    //���ý���������ʼλ��
    //ccp(0,0)��ʾ����
    progress->setMidpoint(ccp(0,0));
 
    //���ý�������ID
    progress->setTag(100);
 
    //����һ����ʱ��
    schedule(schedule_selector(Progress::scheduleFunc), 0.1f);
 
    return true;
}
 
void Progress::scheduleFunc(float dt)
{
    //ͨ����������ID�õ�������
    CCProgressTimer* progress = (CCProgressTimer*)getChildByTag(100);
 
   //����progress�Ľ��ȣ�ÿ����һ�ν��ȼ�һ
    progress->setPercentage(progress->getPercentage() + 1);
     
     //�����ȴ��ڻ��ߵ���100ʱ
    if(progress->getPercentage() >= 100)
    {
          //��ֹ��ʱ��
        unscheduleAllSelectors();
    }
}
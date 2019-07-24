#ifndef __AchievementsScene_H__
#define __AchievementsScene_H__

#include "cocos2d.h"

USING_NS_CC;

enum AchievementsSceneDrawingOrder : unsigned int {
    AchievementsSceneDrawingOrderBackground = 0,
    AchievementsSceneDrawingOrder
};

class AchievementsScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(AchievementsScene);
private:
    int _numPages;
    int _pageNumber;
    MenuItemSprite* _back;
    MenuItemSprite* _next;
    Layer* _pageLayer;
    
    Point _touchStart;

    void onBack(Ref* sender);
    void onNext(Ref* sender);
    void onMenu(Ref* sender);
    void moveBack();
    void moveNext();
    void scroll();
    
    bool onTouchBegan(Touch * touch, Event * event);
    void onTouchEnded(Touch * touch, Event * event);
};

#endif // __AchievementsScene_H__

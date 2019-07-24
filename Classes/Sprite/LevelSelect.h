#ifndef __LevelSelect_H__
#define __LevelSelect_H__

#include "cocos2d.h"

USING_NS_CC;

enum LevelSelectDrawingOrder : unsigned int {
    LevelSelectDrawingOrderBackground = 0,
    LevelSelectDrawingOrderNumber
};

enum LevelStatus : unsigned int {
    LevelStatusInactive = 1,
    LevelStatusActive
};

enum LevelStarStatus : unsigned int {
    LevelStarStatusActive = 0,
    LevelStarStatusInactive,
    LevelStarStatusDisable
};


class LevelSelect : public Sprite
{
public:
    
    static LevelSelect * create(int level, int pageIndex);
    bool init(int level, int pageIndex);

    Size getLevelContentSize();
    void setLevelStatus(unsigned int levelStatus, int starNumber);
private:
    const int STAR_NUMBER = 3;
    int _level;
    unsigned int _levelStatus;
    unsigned int _starNumber;
    int _pageIndex;
    Sprite *_background;
    Vector<Sprite*> _starVector;
    
    void initBackground();
    void onTouchClickCallBack(Ref* pSender);
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnd(Touch* touch, Event* event);
};

#endif 

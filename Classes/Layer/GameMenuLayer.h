#ifndef __GameMenuLayer_H__
#define __GameMenuLayer_H__

#include "cocos2d.h"
USING_NS_CC;

enum GameMenuLayerDrawingOrder : unsigned int {
    GameMenuLayerDrawingOrderBackground = 0,
    GameMenuLayerDrawingOrderButton,
    GameMenuLayerDrawingOrderOthers
};

class GameMenuLayer : public cocos2d::Layer
{
public:
    virtual bool init();

    CREATE_FUNC(GameMenuLayer);
    
    Size getLayerContentSize();
private:
    Sprite* _background;
    
    // buttons
    void onResume(Ref* sender);
    void onRestart(Ref* sender);
    void onChoose(Ref* sender);
    void onOptions(Ref* sender);
    void onMainMenu(Ref* sender);
    void onExit(Ref* sender);
};

#endif // __GameMenuLayer_H__

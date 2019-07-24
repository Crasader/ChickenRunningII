#ifndef __OptionsScene_H__
#define __OptionsScene_H__

#include "cocos2d.h"

USING_NS_CC;


enum OptionsSceneDrawingOrder : unsigned int {
    OptionsSceneDrawingOrderBackground = 0,
    OptionsSceneDrawingOrderButton,
    OptionsSceneDrawingOrder
};

class OptionsScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(OptionsScene);

private:
    Sprite* _soundOn;
    Sprite* _soundOff;
    Sprite* _musicOn;
    Sprite* _musicOff;
    Sprite* _shakeOn;
    Sprite* _shakeOff;
    
    LayerColor* _resetLayer;
    bool _resetLayerUp;

    void onReset(Ref* sender);
    void onBack(Ref* sender);
    void onResetConfirmYes(Ref* sender);
    void onResetConfirmCancel(Ref* sender);
    void updateOptions();
    
    bool onTouchBegan(Touch * touch, Event * event);
    void onTouchEnded(Touch * touch, Event * event);
};

#endif // __OptionsScene_H__

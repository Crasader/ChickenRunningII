#ifndef __MapScene_H__
#define __MapScene_H__

#include "cocos2d.h"
USING_NS_CC;

enum MapSceneDrawingOrder : unsigned int {
    MapSceneDrawingOrderBackground = 0,
    MapSceneDrawingOrderFootPrint,
    MapSceneDrawingOrderOther
};

class MapScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    static Scene* sceneWithStage(int stage);
    
    virtual bool init();

    CREATE_FUNC(MapScene);
private:
    bool _stageLocked1;
    bool _stageLocked2;
    bool _stageLocked3;
    bool _stageLocked4;
    
    cocos2d::Vec2 _forestPoint;
    cocos2d::Vec2 _cavesPoint;
    cocos2d::Vec2 _beachPoint;
    cocos2d::Vec2 _shipPoint;
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnd(Touch* touch, Event* event);
    void onBack(Ref* sender);
    
    void highlight(int stage);
};

#endif // __MapScene_H__

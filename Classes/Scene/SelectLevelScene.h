#ifndef __SelectLevelScene_H__
#define __SelectLevelScene_H__

#include "cocos2d.h"
#include "LevelSelectLayer.h"

USING_NS_CC;

enum SelectLevelSceneDrawingOrder : unsigned int {
    SelectLevelSceneDrawingOrderBackground = 0,
    SelectLevelSceneDrawingOrderOther,
    SelectLevelSceneDrawingOrderLayer
};


class SelectLevelScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(SelectLevelScene);
private:
    void initBackground();
    void initMenuItems();
    
    void initOthers();
    void showLevels();
    
    Point touchStart;
    int _stage;
    int _startingLevel;
    int _levelToLoad;
    bool _levelLoading;
    
    LevelSelectLayer* _levelSelectLayer;
    
    MenuItemSprite* _preMenuItem;
    MenuItemSprite* _nextMenuItem;
    void onPreCallback(Ref* pSender);
    void onNextCallback(Ref* pSender);
    void setScrollPage();
    
    void onBack(Ref* sender);
//    void updateDifficulty();
    
//    void loadLevel(Ref* sender);

};

#endif // __SelectLevelScene_H__

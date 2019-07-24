#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"

USING_NS_CC;

// tags
typedef enum {
    GameTagMoves = 1,
    GameTagLevelCompleteBackground = 2,
    GameTagLevelComplete = 3,
    GameTagLevelCompleteLabel = 4,
    GameTagLevelCompletePerfect = 5,
    GameTagAchievementLayer = 6,
    GameTagMessage = 7,
    GameTagLayerColor = 8,
    GameTagTiles = 100,
    GameTagKeys = 200,
} GameTags;

typedef enum {
    GameMessageNoMessage = 0,
    GameMessageSwipeScreen = 1,
    GameMessageNoMovesMenu = 2,
    GameMessageNoMovesShake = 3
} GameMessages;

enum GameSceneDrawingOrder : unsigned int {
    GameSceneDrawingOrderBackground = 0,
    GameSceneDrawingOrderTileBackgound,
    GameSceneDrawingOrderTile,
    GameSceneDrawingOrderMenuAndLabel,
    GameSceneDrawingOrderMessageLayer,
    GameSceneDrawingOrderColorLayer,
    GameSceneDrawingOrderMenuLayer,
    GameSceneDrawingOrderIntroLayer
};

class GameScene : public cocos2d::Layer
{
public:
    GameScene();
    ~GameScene();
    
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameScene);

    void removeMenuLayer();
    void addIntroLayer();
private:
    Size _visibleSize;
    int _message;
    bool  _won;
    bool  _firstMove;
    bool  _isAchievementActive;
    Point  _touchStart;
    Layer* _tileLayer;
    Sprite* _stepBg;
 
    void setCurrentGame();
    void unsetCurrentGame();

    void restartLevel();
    void moveKeys(int dir);
    void onCompletedLevel();
    void messageDisplay(int messageToDisplay);
    void onRemoveMessage();
    void unlockAchievement(int achievementId);
    void onRemoveAchievement();
    void onMenu(Ref* sender);
    void onBack(Ref* sender);
    void shake();

    bool onTouchBegan(Touch * touch, Event *event);
    void onTouchEnded(Touch * touch, Event *event);
    
    void showAdmobInterstitial(float dt);
    
};

#endif // __GameScene_H__

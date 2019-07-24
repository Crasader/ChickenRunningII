//
//  LevelListLayer.h
//  HuaRong
//
//  Created by kangbiao on 15/5/27.
//
//

#ifndef __GameLayer__
#define __GameLayer__

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
    GameTagTiles = 100,
    GameTagKeys = 200
} GameTags;


enum GameLayerDrawingOrder : unsigned int {
    GameLayerDrawingOrderBackground = 0,
    GameLayerDrawingOrderTiles
};

class GameLayer : public Layer
{
public:
    GameLayer();
    ~GameLayer();

    virtual bool init();
    
    CREATE_FUNC(GameLayer);
private:
    bool _won;
    bool _firstMove;
    
    void initBackground();
    void initTiles();
    
//    bool onTouchBegan(Touch * touch, Event *event);
//    void onTouchEnded(Touch * touch, Event *event);
};


#endif /* defined(__GameLayer__) */

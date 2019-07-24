//
//  LevelListLayer.h
//  HuaRong
//
//  Created by kangbiao on 15/5/27.
//
//

#ifndef __GameIntroLayer__
#define __GameIntroLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Pagination.h"

USING_NS_CC;
using namespace ui;

enum GameIntroLayerDrawingOrder : unsigned int {
    GameIntroLayerDrawingOrderColorLayer = 0,
    GameIntroLayerDrawingOrderTips
};

class GameIntroLayer : public cocos2d::Layer
{
public:
    GameIntroLayer();
    ~GameIntroLayer();

    virtual bool init();
    
    CREATE_FUNC(GameIntroLayer);
private:
    void initIntroOthers();
    bool onTouchBegan(Touch * touch, Event *event);
    void onTouchEnded(Touch * touch, Event *event);
};


#endif /* defined(__GameIntroLayer__) */

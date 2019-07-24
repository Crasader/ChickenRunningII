#ifndef __GameWinLayer_H__
#define __GameWinLayer_H__

#include "cocos2d.h"
USING_NS_CC;

enum GameWinLayerDrawingOrder : unsigned int {
    GameWinLayerDrawingOrderBackground = 0,
    GameWinLayerDrawingOrderButton,
    GameWinLayerDrawingOrderOthers
};

class GameWinLayer : public cocos2d::Layer
{
public:
    virtual bool init();

    CREATE_FUNC(GameWinLayer);
    
    Size getLayerContentSize();
    void setStars(int starNumber);
    void setString(std::string stringLabel);
    
private:
    Sprite* _background;
    Vector<Sprite*> _starVector;
    Label* _strLabel;
    
    // buttons
    void onMenu(Ref* sender);
    void onRestart(Ref* sender);
    void onNextlevel(Ref* sender);
};

#endif // __GameWinLayer_H__

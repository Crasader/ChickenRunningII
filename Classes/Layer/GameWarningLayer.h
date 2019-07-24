#ifndef __GameWarningLayer_H__
#define __GameWarningLayer_H__

#include "cocos2d.h"
USING_NS_CC;

enum GameWarningLayerDrawingOrder : unsigned int {
    GameWarningLayerDrawingOrderBackground = 0,
    GameWarningLayerDrawingOrderButton,
    GameWarningLayerDrawingOrderOthers
};

class GameWarningLayer : public cocos2d::Layer
{
public:
    virtual bool init();

    CREATE_FUNC(GameWarningLayer);
    
    Size getLayerContentSize();
    void setString(std::string stringLabel);
    
private:
    Sprite* _background;
    Label* _strLabel;
    
    // buttons
    void onClose(Ref* sender);
    void onRestart(Ref* sender);
};

#endif // __GameWarningLayer_H__

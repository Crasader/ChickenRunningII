#ifndef __WarningLayer_H__
#define __WarningLayer_H__

#include "cocos2d.h"
USING_NS_CC;

enum WarningLayerDrawingOrder : unsigned int {
    WarningLayerDrawingOrderLayer = 0,
    WarningLayerDrawingOrderBackground,
    WarningLayerDrawingOrderButton,
    WarningLayerDrawingOrderOthers
};

class WarningLayer : public cocos2d::Layer
{
public:
    virtual bool init();

    CREATE_FUNC(WarningLayer);
    
    Size getLayerContentSize();
    void setString(std::string stringLabel);
    
private:
    Sprite* _background;
    Label* _strLabel;
    Layer* _resetLayer;
    
    // buttons
    void onClose(Ref* sender);
    void onConfirm(Ref* sender);
};

#endif // __WarningLayer_H__

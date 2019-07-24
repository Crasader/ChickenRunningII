#ifndef __InstructionsScene_H__
#define __InstructionsScene_H__

#include "cocos2d.h"

USING_NS_CC;

enum InstructionsSceneDrawingOrder : unsigned int {
    InstructionsSceneDrawingOrderBackground = 0,
    InstructionsSceneDrawingOrderLayer,
    InstructionsSceneDrawingOrderOthers
};

class InstructionsScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(InstructionsScene);
    
private:
    void onBack(Ref* sender);
    
    void initBackground();
    void initContent();
};

#endif // __InstructionsScene_H__

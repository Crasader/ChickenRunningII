#ifndef __MenuScene_H__
#define __MenuScene_H__

#include "cocos2d.h"

enum MenuSceneDrawingOrder : unsigned int {
    MenuSceneDrawingOrderBackground = 0,
    MenuSceneDrawingOrderOther,
    MenuSceneDrawingOrderButton,
    MenuSceneDrawingOrderLayer
};

class MenuScene : public cocos2d::Layer
{
public:
    MenuScene();
    ~MenuScene();
    
    static cocos2d::Scene* createScene();

    CREATE_FUNC(MenuScene);
private:
    virtual bool init();
    
    void initBackground();
    void initSettingIcon();
    
    void onPlay(Ref* pSender);
    void onInstructions(Ref* pSender);
    void onReset(Ref* pSender);

    
    void showAdmobInterstitial(float dt);
};

#endif // __MenuScene_H__

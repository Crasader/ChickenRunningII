//
//  LevelListLayer.h
//  HuaRong
//
//  Created by kangbiao on 15/5/27.
//
//

#ifndef __LevelSelectLayer__
#define __LevelSelectLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Pagination.h"

USING_NS_CC;
using namespace ui;

enum LevelSelectLayerDrawingOrder : unsigned int {
    LevelSelectLayerDrawingOrderBackground = 0,
    LevelSelectLayerDrawingOrderLevel,
    LevelSelectLayerDrawingOrderButton
};

class LevelSelectLayer : public cocos2d::Layer
{
public:
    LevelSelectLayer();
    ~LevelSelectLayer();

    virtual bool init();
    
    CREATE_FUNC(LevelSelectLayer);
private:
    CC_SYNTHESIZE(int, _currentPage, CurrentPage);
    CC_SYNTHESIZE(int, _maxPage, MaxPage);
    PageView* _pageView;
    Pagination* _pagination;

    void initPageView();
    void pageViewEvent(Ref * pSender, PageView::EventType type);
    void setScrollPage(int currPage);
};


#endif /* defined(__LevelSelectLayer__) */

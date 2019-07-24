//
//  LevelListLayer.h
//  HuaRong
//
//  Created by kangbiao on 15/5/27.
//
//

#ifndef __LevelSelectLayer__
#define __InstructionLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Pagination.h"

USING_NS_CC;
using namespace ui;

enum InstructionLayerDrawingOrder : unsigned int {
    InstructionLayerDrawingOrderBackground = 0,
    InstructionLayerDrawingOrderPage,
    InstructionLayerDrawingOrderButton
};

class InstructionLayer : public cocos2d::Layer
{
public:
    InstructionLayer();
    ~InstructionLayer();

    virtual bool init();
    
    CREATE_FUNC(InstructionLayer);
private:
    MenuItemSprite* _preMenuItem;
    MenuItemSprite* _nextMenuItem;
    void initMenuItems();
    void onPreCallback(Ref* pSender);
    void onNextCallback(Ref* pSender);
    void pageViewEvent(Ref * pSender, PageView::EventType type);
    
    void onItems(Ref* pSender);
    void onCredits(Ref* pSender);
    void onGoals(Ref* pSender);
    void onTips(Ref* pSender);
    
    int _currentPage;
    int _maxPage;
    Size _visibleSize;
    Size _pageSize;
    PageView* _pageView;
    Pagination* _pagination;

    void initPageView();
    ListView* getItemsList();
    ScrollView* getTips();
    ScrollView* getGoals();
    Layout* getCredits();

    void setScrollPage();
    
    const std::string _itemImageNames[5] = {
        "instr_items_chicken.png",
        "instr_items_insect.png",
        "instr_items_key.png",
        "instr_items_dooropen.png",
        "instr_items_doorclose.png"
    };

    const std::string _itemTitles[5] = {
        "Chicken",
        "Insect",
        "Door Key",
        "Door Open",
        "Door Close"
    };

    const std::string _itemDesces[5] = {
        "You can move this to left, right and down",
        "Insect",
        "You can open/close door through move to key",
        "You can pass through",
        "You can't pass"
    };

};


#endif /* defined(__InstructionLayer__) */

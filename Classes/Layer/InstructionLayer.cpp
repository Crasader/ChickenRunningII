//
//  LevelListLayer.cpp
//  HuaRong
//
//  Created by kangbiao on 15/5/27.
//
//

#include "InstructionLayer.h"
#include "GameData.h"
#include "Sound.h"

using namespace ui;

//InstructionLayer::_itemImageNames = {};

InstructionLayer::InstructionLayer()
:_currentPage(0)
,_maxPage(0)
{
    
}

InstructionLayer::~InstructionLayer() {
    
}

bool  InstructionLayer::init() {
    if ( ! Layer::init() )
    {
        return false;
    }
  
    _visibleSize = Director::getInstance()->getVisibleSize();
    _pageSize = Size(_visibleSize.width * 0.75f,
                     _visibleSize.height * 0.6);
    
//    this->initMenuItems();
    this->initPageView();
    
    return true;
}

#pragma mark - for init function

void InstructionLayer::initMenuItems() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto arrowIcon = Sprite::createWithSpriteFrameName("select_level_arrow_active.png");
    arrowIcon->setFlippedX(true);
    _preMenuItem = MenuItemSprite::create(arrowIcon,
                                          arrowIcon,
                                          CC_CALLBACK_1(InstructionLayer::onPreCallback, this));
    _preMenuItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    _preMenuItem->setPosition(0,
                              visibleSize.height / 2);
    
    auto nextArrowIcon = Sprite::createWithSpriteFrameName("select_level_arrow_active.png");
    _nextMenuItem = MenuItemSprite::create(nextArrowIcon,
                                           nextArrowIcon,
                                           CC_CALLBACK_1(InstructionLayer::onNextCallback, this));
    _nextMenuItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    _nextMenuItem->setPosition(visibleSize.width,
                               visibleSize.height / 2);
    
//    auto segmentBg = Sprite::createWithSpriteFrameName("instr_segment_bg.png");
//    segmentBg->setPosition(visibleSize.width / 2.0f,
//                           visibleSize.height * 0.8f);
//    this->addChild(segmentBg);
//    
//    auto itemsActive = Sprite::createWithSpriteFrameName("instr_segment_active.png");
//    auto itemLabel   = Sprite::createWithSpriteFrameName("instr_segment_items.png");
//    itemLabel->setPosition(itemsActive->getContentSize().width / 2.0f,
//                           itemsActive->getContentSize().height / 2.0f);
//    itemsActive->addChild(itemLabel);
//    
//    auto itemsInactive = Sprite::createWithSpriteFrameName("instr_segment_inactive.png");
//    itemLabel   = Sprite::createWithSpriteFrameName("instr_segment_items.png");
//    itemLabel->setPosition(itemsInactive->getContentSize().width / 2.0f,
//                           itemsInactive->getContentSize().height / 2.0f);
//    itemsInactive->addChild(itemLabel);
//
//    auto itemsDisable = Sprite::createWithSpriteFrameName("instr_segment_inactive.png");
//    itemLabel   = Sprite::createWithSpriteFrameName("instr_segment_items.png");
//    itemLabel->setPosition(itemsInactive->getContentSize().width / 2.0f,
//                           itemsInactive->getContentSize().height / 2.0f);
//    itemsDisable->addChild(itemLabel);
//
//    auto normalMenuItemItems = MenuItemSprite::create(itemsInactive,
//                                                      itemsInactive);
//    auto selectMenuItemItems = MenuItemSprite::create(itemsActive,
//                                                      itemsActive);
//    auto disableMenuItemItems = MenuItemSprite::create(itemsDisable,
//                                                       itemsDisable);
//    auto items = MenuItemToggle::createWithCallback(
//                                                    CC_CALLBACK_1(InstructionLayer::onItems, this),
//                                                    normalMenuItemItems,
//                                                    selectMenuItemItems,
//                                                    disableMenuItemItems, NULL);
//    items->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
//    items->setPosition(segmentBg->getContentSize().width / 4.0f,
//                       segmentBg->getContentSize().height / 2.0f);
    
    auto menu = Menu::create(_preMenuItem, _nextMenuItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, InstructionLayerDrawingOrderButton);
}

void InstructionLayer::initPageView() {
    _pageView = PageView::create();
    _pageView->setSize(_pageSize);
    _pageView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _pageView->removeAllPages();
    
    _pageView->ignoreAnchorPointForPosition(false);

    _pageView->insertPage(this->getItemsList(), 0);
//    _pageView->insertPage(this->getTips(), 1);
//    _pageView->insertPage(this->getGoals(), 2);
//    _pageView->insertPage(this->getCredits(), 3);
    
    _pageView->setPosition(Vec2(_visibleSize.width / 2,
                                _visibleSize.height * 0.4f));
    _pageView->addEventListener(CC_CALLBACK_2(InstructionLayer::pageViewEvent, this));
    _pageView->setPropagateTouchEvents(false);  //不仅要设置子节点和孙节点，还要设置自己的不繁衍
    _pageView->setSwallowTouches(true);
    this->addChild(_pageView, InstructionLayerDrawingOrderPage);
}

#pragma mark - for callback function

ListView* InstructionLayer::getItemsList() {
    auto itemsList = ListView::create();
    itemsList->setDirection(ScrollView::Direction::VERTICAL);
    itemsList->setBounceEnabled(true);
    itemsList->setContentSize(_pageSize);
    
    for (int i = 0; i < 5; i++) {
        auto itemBackground = Sprite::createWithSpriteFrameName("instr_items_bg.png");
        auto layoutItem = Layout::create();
        layoutItem->setContentSize(Size(_pageSize.width,
                                        itemBackground->getContentSize().height));
        itemBackground->setPosition(Vec2(layoutItem->getContentSize().width / 2.0f,
                                         layoutItem->getContentSize().height / 2.0f));
        layoutItem->addChild(itemBackground);
        
        auto itemImage = Sprite::createWithSpriteFrameName(_itemImageNames[i]);
        itemImage->setPosition(Vec2(itemImage->getContentSize().width / 2.0f,
                                    layoutItem->getContentSize().height / 2.0f));
        itemImage->setScale(0.8f);
        layoutItem->addChild(itemImage);
        
        auto itemTitle = Label::createWithBMFont("fonts/carterone-40-white.fnt", _itemTitles[i]);
        itemTitle->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        itemTitle->setPosition(Vec2(layoutItem->getContentSize().width / 4.0f,
                                    layoutItem->getContentSize().height * 0.7f));
        layoutItem->addChild(itemTitle);
        
        auto itemDesc = Label::createWithBMFont("fonts/carterone-20-white.fnt", _itemDesces[i]);
        itemDesc->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        //        itemDesc->setScale(0.5f);
        itemDesc->setDimensions(layoutItem->getContentSize().width * 0.7f,
                                layoutItem->getContentSize().height * 0.4f);
        itemDesc->setPosition(Vec2(layoutItem->getContentSize().width / 4.0f,
                                   layoutItem->getContentSize().height * 0.4f));
        layoutItem->addChild(itemDesc);
        
        itemsList->addChild(layoutItem);
        itemsList->setItemsMargin(layoutItem->getContentSize().height * 0.2f);
    }
    
    return itemsList;
}

ScrollView* InstructionLayer::getTips() {
    ScrollView* tips = ScrollView::create();
    tips->setDirection(ScrollView::Direction::VERTICAL);
    tips->setBounceEnabled(true);
    tips->setContentSize(_pageSize);
    
    auto tipsTitle = Label::createWithBMFont("fonts/carterone-40-white.fnt", "Tips");
    tipsTitle->setPosition(Vec2(tips->getContentSize().width / 2.0f,
                                tips->getContentSize().height * 0.8f));
    tips->addChild(tipsTitle);
    
    return tips;
}

ScrollView* InstructionLayer::getGoals() {
    ScrollView* goals = ScrollView::create();
    goals->setDirection(ScrollView::Direction::VERTICAL);
    goals->setBounceEnabled(true);
    goals->setContentSize(_pageSize);
    
    auto goalsTitle = Label::createWithBMFont("fonts/carterone-40-white.fnt", "Goals");
    goalsTitle->setPosition(Vec2(goals->getContentSize().width / 2.0f,
                                goals->getContentSize().height * 0.8f));
    goals->addChild(goalsTitle);
    
    return goals;
}

Layout* InstructionLayer::getCredits() {
    Layout* credits = Layout::create();
    
    return credits;
}


void InstructionLayer::onPreCallback(Ref* pSender) {
    Sound::getInstance()->playClick();
    _currentPage--;
    this->setScrollPage();
}

void InstructionLayer::onNextCallback(Ref* pSender) {
    Sound::getInstance()->playClick();
    _currentPage++;
    this->setScrollPage();
}

void InstructionLayer::pageViewEvent(Ref * pSender, PageView::EventType type) {
    switch (type) {
        case PageView::EventType::TURNING: {
            PageView * pageView = dynamic_cast<PageView *>(pSender);
            _currentPage = pageView->getCurPageIndex();
            this->setScrollPage();
//            log("%ld", pageView->getCurPageIndex() + 1);
        }
        break;
        
        default:
            break;
    }
}

void InstructionLayer::onItems(Ref* pSender) {

}

void InstructionLayer::onCredits(Ref* pSender) {
    
}

void InstructionLayer::onGoals(Ref* pSender) {
    
}

void InstructionLayer::onTips(Ref* pSender) {
    
}



#pragma mark - for private function
void InstructionLayer::setScrollPage() {
    _preMenuItem->setVisible(true);
    _nextMenuItem->setVisible(true);
    
    if (_currentPage >= 0 && _currentPage < _maxPage) {
        _pageView->scrollToPage(_currentPage);
        _pagination->setCurrentPaginationPosition(_currentPage);
    }
    
    if (_currentPage <= 0) {
        _currentPage = 0;
        _preMenuItem->setVisible(false);
    }
    
    if (_currentPage >= _maxPage - 1) {
        _currentPage = _maxPage - 1;
        _nextMenuItem->setVisible(false);
    }

}

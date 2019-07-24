//
//  LevelListLayer.cpp
//  HuaRong
//
//  Created by kangbiao on 15/5/27.
//
//

#include "LevelSelectLayer.h"
#include "LevelSelect.h"
#include "Levels.h"
#include "GameData.h"
#include "Sound.h"

using namespace ui;

LevelSelectLayer::LevelSelectLayer()
:_currentPage(0)
,_maxPage(0)
{
    
}

LevelSelectLayer::~LevelSelectLayer() {
    
}

bool  LevelSelectLayer::init() {
    if ( ! Layer::init() )
    {
        return false;
    }

    this->initPageView();
    
    return true;
}

#pragma mark - for init function


void LevelSelectLayer::initPageView() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto pageSize = Size(Size(visibleSize.width * 0.7f,
                              visibleSize.height * 0.6));
    _currentPage = 0;
    int minLevelNumber = GameData::getInstance()->getStartLevel();
    int maxLevelNumber = GameData::getInstance()->getEndLevel();
    int currentLevelNumber = minLevelNumber;
    
    const float VAR_LEVEL = 1.1f;
    auto templevel = LevelSelect::create(0, 0);
    int MAX_COL = pageSize.width / (templevel->getLevelContentSize().width * VAR_LEVEL);
    int MAX_ROW = pageSize.height / (templevel->getLevelContentSize().height * VAR_LEVEL);
    float LEVEL_WIDTH_MARGIN = templevel->getLevelContentSize().width * VAR_LEVEL / 2.0f;
    float LEVEL_HEIGHT_MARGIN = templevel->getLevelContentSize().height * VAR_LEVEL / 2.0f;
    
    _maxPage = (maxLevelNumber - minLevelNumber) / (MAX_COL * MAX_ROW);
    if ((maxLevelNumber - minLevelNumber) % (MAX_COL * MAX_ROW)) _maxPage++;
    
    _pageView = PageView::create();
    _pageView->setSize(pageSize);
    _pageView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _pageView->removeAllPages();
    
    _pageView->ignoreAnchorPointForPosition(false);
    
    for (int i = 0; i < _maxPage; i++) {
        auto pageBox = VBox::create();
        pageBox->setContentSize(pageSize);
        for (int row = 0; row < MAX_ROW; row++) {
            auto innerRowBox = HBox::create();
            
            for (int col = 0; col < MAX_COL; col++) {
//                int number = row * MAX_COL + col + i * MAX_COL * MAX_ROW + 1;
                
                if (currentLevelNumber <= maxLevelNumber) {
                    auto innerColumnBox = VBox::create();
                    auto level = LevelSelect::create(currentLevelNumber, i);
                    auto l = Levels::getInstance()->getLevels().at(currentLevelNumber - 1);
                    unsigned int leveStatus = LevelStatusInactive;
                    if (l->getComplete() || currentLevelNumber == minLevelNumber) {
                        leveStatus = LevelStatusActive;
                    } else if (currentLevelNumber != 1) {
                        auto preLevel = Levels::getInstance()->getLevels().at(currentLevelNumber - 2);
                        if (preLevel->getComplete()) {
                            leveStatus = LevelStatusActive;
                        }
                    }
                    
                    level->setLevelStatus(leveStatus, l->getPerfect());
                    innerColumnBox->addChild(level);
                    
                    auto parameterCol = LinearLayoutParameter::create();
                    parameterCol->setMargin(Margin(LEVEL_WIDTH_MARGIN, 0, LEVEL_WIDTH_MARGIN, 0));
                    innerColumnBox->setLayoutParameter(parameterCol);
                    
                    innerRowBox->addChild(innerColumnBox);
                }
                currentLevelNumber++;
            }
            auto parameter = LinearLayoutParameter::create();
            parameter->setMargin(Margin(0, LEVEL_HEIGHT_MARGIN, 0, LEVEL_HEIGHT_MARGIN));
            innerRowBox->setLayoutParameter(parameter);
            
            pageBox->addChild(innerRowBox);
        }
        
        auto parameter = LinearLayoutParameter::create();
        parameter->setMargin(Margin(LEVEL_WIDTH_MARGIN * 2 * 3 * 2, 0, 0, 0));
        pageBox->setLayoutParameter(parameter);
        
        _pageView->insertPage(pageBox, i);
        
    }
    _pageView->cocos2d::Node::setPosition(visibleSize.width / 2,
                                          visibleSize.height / 2);
    _pageView->addEventListener(CC_CALLBACK_2(LevelSelectLayer::pageViewEvent, this));
    _pageView->setPropagateTouchEvents(false);  //不仅要设置子节点和孙节点，还要设置自己的不繁衍
    _pageView->setSwallowTouches(true);
    this->addChild(_pageView, LevelSelectLayerDrawingOrderLevel);
    
    // for pagination
    _pagination = Pagination::create(_maxPage);
    _pagination->setPosition(visibleSize.width / 2,
                             visibleSize.height * 0.15f);
    this->addChild(_pagination, LevelSelectLayerDrawingOrderLevel);
    
    this->setScrollPage(_currentPage);
}

#pragma mark - for callback function



void LevelSelectLayer::pageViewEvent(Ref * pSender, PageView::EventType type) {
    switch (type) {
        case PageView::EventType::TURNING: {
            PageView * pageView = dynamic_cast<PageView *>(pSender);
            _currentPage = pageView->getCurPageIndex();
            this->setScrollPage(_currentPage);
//            log("%ld", pageView->getCurPageIndex() + 1);
        }
        break;
        
        default:
            break;
    }
}

#pragma mark - for private function
void LevelSelectLayer::setScrollPage(int currPage) {
    _pageView->scrollToPage(currPage);
    _pagination->setCurrentPaginationPosition(currPage);
}

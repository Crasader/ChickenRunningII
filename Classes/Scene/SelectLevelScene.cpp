#include "SelectLevelScene.h"
#include "GameData.h"
#include "Levels.h"
#include "LevelSelect.h"
#include "Sound.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "Options.h"

#include "MapScene.h"
#include "SonarFrameworks.h"

Scene* SelectLevelScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SelectLevelScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SelectLevelScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    _levelToLoad = -1;
    _levelLoading = false;
    
    this->initBackground();
    this->initOthers();
    this->showLevels();
    this->initMenuItems();

    SonarCocosHelper::AdMob::hideBannerAd();

    return true;
}

void SelectLevelScene::initOthers() {
   //  auto visibleSize = Director::getInstance()->getVisibleSize();

}


void SelectLevelScene::initBackground() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // background
    Sprite* background = Sprite::create("images/select_level_background.png");
    background->setPosition(visibleSize.width / 2,
                            visibleSize.height / 2);
    this->addChild(background, SelectLevelSceneDrawingOrderBackground);
    
    // header
    auto header = Sprite::createWithSpriteFrameName("select_level_header.png");
    header->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    header->setPosition(visibleSize.width / 2,
                        visibleSize.height );
    this->addChild(header, SelectLevelSceneDrawingOrderOther);
}

void SelectLevelScene::showLevels() {
    // display the level numbers
    _startingLevel = 0;
//    auto visibleSize = Director::getInstance()->getVisibleSize();
    _levelSelectLayer = LevelSelectLayer::create();
//    levelSelectLayer->setPosition(visibleSize.width / 2 ,
//                                  visibleSize.height / 2);
    this->addChild(_levelSelectLayer, SelectLevelSceneDrawingOrderLayer);
}

//void SelectLevelScene::updateDifficulty() {
//
//    float x = 32, y = 380;
//    for(int i = _startingLevel; i < _startingLevel + 30; i++) {
//        Level* level = Levels::getInstance()->getLevels().at(i - 1);
//        auto levelSelect = LevelSelect::create(i, 0);
//        levelSelect->setPosition(x, y);
//        this->addChild(levelSelect, SelectLevelSceneDrawingOrderOther);
//        
//        bool dimm = true;
//        switch (Options::getInstance()->difficulty) {
//            case GameDifficultyEasy:
//                if (level->getCompleteEasy()) dimm = false;
//                break;
//            case GameDifficultyMedium:
//                if (level->getCompleteMedium()) dimm = false;
//                break;
//            case GameDifficultyHard:
//                if (level->getCompleteHard()) dimm = false;
//                break;
//        }
////        if(dimm) {
////            num.opacity = 64;
////        } else {
////            num.opacity = 255;
////        }
//    }
//}


void SelectLevelScene::onBack(Ref* sender) {
    log("SelectLevelScene onBack");
    Sound::getInstance()->playClick();
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.3f, MapScene::createScene(), true));
}



void SelectLevelScene::initMenuItems() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto arrowIcon = Sprite::createWithSpriteFrameName("select_level_arrow_active.png");
    arrowIcon->setFlippedX(true);
    _preMenuItem = MenuItemSprite::create(arrowIcon,
                                          arrowIcon,
                                          CC_CALLBACK_1(SelectLevelScene::onPreCallback, this));
    _preMenuItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    _preMenuItem->setPosition(0,
                              visibleSize.height / 2);
    
    auto nextArrowIcon = Sprite::createWithSpriteFrameName("select_level_arrow_active.png");
    _nextMenuItem = MenuItemSprite::create(nextArrowIcon,
                                           nextArrowIcon,
                                           CC_CALLBACK_1(SelectLevelScene::onNextCallback, this));
    _nextMenuItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    _nextMenuItem->setPosition(visibleSize.width ,
                               visibleSize.height / 2);
    
    // back menu
    auto backItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("select_level_back.png"),
                                           Sprite::createWithSpriteFrameName("select_level_back2.png"),
                                           CC_CALLBACK_1(SelectLevelScene::onBack, this));
    backItem->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    backItem->setPosition(visibleSize.width * 0.05f,
                          visibleSize.height * 0.1f);
    
    auto menu = Menu::create(_preMenuItem, _nextMenuItem, backItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, LevelSelectLayerDrawingOrderButton);
    
    this->setScrollPage();
}

void SelectLevelScene::onPreCallback(Ref* pSender) {
    Sound::getInstance()->playClick();
    _levelSelectLayer->setCurrentPage(_levelSelectLayer->getCurrentPage() - 1);
    this->setScrollPage();
}

void SelectLevelScene::onNextCallback(Ref* pSender) {
    Sound::getInstance()->playClick();
    _levelSelectLayer->setCurrentPage(_levelSelectLayer->getCurrentPage() + 1);
    this->setScrollPage();
}

void SelectLevelScene::setScrollPage() {
    _preMenuItem->setVisible(true);
    _nextMenuItem->setVisible(true);
    
    if (_levelSelectLayer->getCurrentPage() >= 0 && _levelSelectLayer->getCurrentPage() < _levelSelectLayer->getMaxPage()) {
        _levelSelectLayer->setScrollPage(_levelSelectLayer->getCurrentPage());
    }
    
    if (_levelSelectLayer->getCurrentPage() <= 0) {
        _levelSelectLayer->setCurrentPage(0);
        _preMenuItem->setVisible(false);
    }
    
    if (_levelSelectLayer->getCurrentPage() >= _levelSelectLayer->getMaxPage() - 1) {
        _levelSelectLayer->setCurrentPage(_levelSelectLayer->getMaxPage() - 1);
        _nextMenuItem->setVisible(false);
    }
    
}
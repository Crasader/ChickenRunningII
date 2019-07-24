#include "GameMenuLayer.h"
#include "Sound.h"
#include "GameData.h"
#include "GameScene.h"
#include "MapScene.h"
#include "OptionsScene.h"
#include "MenuScene.h"
#include "SelectLevelScene.h"

// on "init" you need to initialize your instance
bool GameMenuLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    // background
    _background = Sprite::createWithSpriteFrameName("game_menu_background.png");
//    _background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(_background, GameMenuLayerDrawingOrderBackground);
    
    // header
//    auto header = Sprite::createWithSpriteFrameName("game_menu_header.png");
//    header->setPosition(visibleSize.width / 2, visibleSize.height / 2);
//    this->addChild(header, GameMenuLayerDrawingOrderButton);
//    
//    // status
//    auto statusBackground = Sprite::createWithSpriteFrameName("game_menu_status_background.png");
//    statusBackground->setPosition(visibleSize.width / 2,
//                        visibleSize.height / 2);
//    this->addChild(statusBackground, GameMenuLayerDrawingOrderButton);
//    
//    auto statusLabel = Label::createWithSystemFont(StringUtils::format("%s * LEVEL %d", GameData::getInstance()->stageName().c_str(), GameData::getInstance()->getLevel()), "arial.ttf", 25.0f);
//    statusLabel->setColor(Color3B(147,213,18));
//    statusLabel->setPosition(160, 330);
//    this->addChild(statusLabel, GameMenuLayerDrawingOrderOthers);
    
    // top menu
    auto exit = MenuItemSprite::create(Sprite::createWithSpriteFrameName("game_menu_exit.png"),
                                       Sprite::createWithSpriteFrameName("game_menu_exit2.png"),
                                       CC_CALLBACK_1(GameMenuLayer::onExit, this));
    exit->setPosition(_background->getContentSize().width - exit->getContentSize().width / 2.0f,
                      _background->getContentSize().height - exit->getContentSize().height);
    
    auto resume = MenuItemSprite::create(Sprite::createWithSpriteFrameName("game_menu_resume.png"),
                                         Sprite::createWithSpriteFrameName("game_menu_resume2.png"),
                                         CC_CALLBACK_1(GameMenuLayer::onResume, this));
    resume->setPosition(_background->getContentSize().width / 2,
                        _background->getContentSize().height * 0.7f);
    auto restart = MenuItemSprite::create(Sprite::createWithSpriteFrameName("game_menu_restart.png"),
                                          Sprite::createWithSpriteFrameName("game_menu_restart2.png"),
                                          CC_CALLBACK_1(GameMenuLayer::onRestart, this));
    restart->setPosition(_background->getContentSize().width / 2,
                         resume->getPosition().y - restart->getContentSize().height);
    auto choose = MenuItemSprite::create(Sprite::createWithSpriteFrameName("game_menu_choose.png"),
                                         Sprite::createWithSpriteFrameName("game_menu_choose2.png"),
                                         CC_CALLBACK_1(GameMenuLayer::onChoose, this));
    choose->setPosition(_background->getContentSize().width / 2,
                         restart->getPosition().y - choose->getContentSize().height);
    auto top_menu = Menu::create(resume, restart, choose, exit, NULL);
    top_menu->setPosition(Vec2::ZERO);
    _background->addChild(top_menu, GameMenuLayerDrawingOrderOthers);
    
    // bottom menu
//    auto options = MenuItemSprite::create(Sprite::createWithSpriteFrameName("game_menu_options.png"),
//                                          Sprite::createWithSpriteFrameName("game_menu_options2.png"),
//                                          CC_CALLBACK_1(GameMenuLayer::onOptions, this));
//    options->setPosition(_background->getContentSize().width / 2,
//                         _background->getContentSize().height * 0.3f);
    auto mainmenu = MenuItemSprite::create(Sprite::createWithSpriteFrameName("game_menu_main.png"),
                                            Sprite::createWithSpriteFrameName("game_menu_main2.png"),
                                            CC_CALLBACK_1(GameMenuLayer::onMainMenu, this));
    mainmenu->setPosition(_background->getContentSize().width / 2,
                          _background->getContentSize().height * 0.3f);
    auto bottom_menu = Menu::create(mainmenu, NULL);
    bottom_menu->setPosition(Vec2::ZERO);
    _background->addChild(bottom_menu, GameMenuLayerDrawingOrderOthers);
    
    return true;
}

Size GameMenuLayer::getLayerContentSize() {
    return _background->getContentSize();
}


void GameMenuLayer::onResume(Ref* sender) {
    log("GameMenuLayer onResume");
    Sound::getInstance()->playClick();
    GameData::getInstance()->loadGame();
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.3f, GameScene::createScene(), true));
}

void GameMenuLayer::onRestart(Ref* sender) {
    log("GameMenuLayer onRestart");
    Sound::getInstance()->playRestartLevel();
    GameData::getInstance()->loadLevel();
    GameData::getInstance()->saveGame();
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.3f, GameScene::createScene(), true));
}

void GameMenuLayer::onChoose(Ref* sender) {
    log("GameMenuLayer onChoose");
    Sound::getInstance()->playClick();
    GameData::getInstance()->setReturnToGame(true);
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.3f, SelectLevelScene::createScene(), true));
}

void GameMenuLayer::onOptions(Ref* sender) {
    log("GameMenuLayer onOptions");
    Sound::getInstance()->playClick();
    GameData::getInstance()->setReturnToGame(true);
    GameData::getInstance()->loadGame();
    Director::getInstance()->replaceScene(TransitionFade::create(0.3f, OptionsScene::createScene()));
}

void GameMenuLayer::onMainMenu(Ref* sender) {
    log("GameMenuLayer onMainMenu");
    Sound::getInstance()->playClick();
    
    // delete saved game
    GameData::getInstance()->deleteSavedGame();
    
    // change music
    Sound::getInstance()->startMusicMenu();
    
    // go to menu
    Director::getInstance()->replaceScene(TransitionFade::create(0.3f, MenuScene::createScene()));
}

void GameMenuLayer::onExit(Ref* sender) {
    log("GameMenuLayer onExit");
    static_cast<GameScene*>(this->getParent())->removeMenuLayer();
    
    this->removeFromParent();

}

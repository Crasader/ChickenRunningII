#include "GameWinLayer.h"
#include "Sound.h"
#include "GameData.h"
#include "GameScene.h"
#include "SelectLevelScene.h"

// on "init" you need to initialize your instance
bool GameWinLayer::init()
{
    if ( !Layer::init() ) {
        return false;
    }
    
    // background
    _background = Sprite::createWithSpriteFrameName("game_win_bg.png");
    this->addChild(_background, GameWinLayerDrawingOrderBackground);
    
    // top menu
    Vector<MenuItem *> itemsVector;
    auto menu = MenuItemSprite::create(Sprite::createWithSpriteFrameName("game_win_menu.png"),
                                       Sprite::createWithSpriteFrameName("game_win_menu.png"),
                                       CC_CALLBACK_1(GameWinLayer::onMenu, this));
    menu->setPosition(_background->getContentSize().width / 2.0f,
                      menu->getContentSize().width * 0.3f);
    itemsVector.pushBack(menu);
    
    auto restart = MenuItemSprite::create(Sprite::createWithSpriteFrameName("game_win_restart.png"),
                                          Sprite::createWithSpriteFrameName("game_win_restart.png"),
                                          CC_CALLBACK_1(GameWinLayer::onRestart, this));
    restart->setPosition(_background->getContentSize().width / 2 - menu->getContentSize().width * 1.5f,
                         menu->getContentSize().width * 0.3f);
    itemsVector.pushBack(restart);
    auto nextlevel = MenuItemSprite::create(Sprite::createWithSpriteFrameName("game_win_nextlevel.png"),
                                            Sprite::createWithSpriteFrameName("game_win_nextlevel.png"),
                                          CC_CALLBACK_1(GameWinLayer::onNextlevel, this));
    nextlevel->setPosition(_background->getContentSize().width / 2 + menu->getContentSize().width * 1.5f,
                           menu->getContentSize().width * 0.3f);
    if (GameData::getInstance()->getLevel() < GameData::getInstance()->getEndLevel()) {
        itemsVector.pushBack(nextlevel);
    }
    
    auto top_menu = Menu::createWithArray(itemsVector);// :create(menu, restart, nextlevel, NULL);
    top_menu->setPosition(Vec2::ZERO);
    _background->addChild(top_menu, GameWinLayerDrawingOrderOthers);
    
    for (int i = 0; i < 3; i++) {
        auto starSprite = Sprite::createWithSpriteFrameName("game_win_star_inactive.png");
        starSprite->setPosition(_background->getContentSize().width / 2.0f - starSprite->getContentSize().width * (1.0f - i),
                                _background->getContentSize().height * 0.6f);
        
        _starVector.pushBack(starSprite);
        _background->addChild(starSprite);
    }
    
    _strLabel = Label::createWithBMFont("fonts/carterone-40-white.fnt", "");
    _strLabel->setPosition(_background->getContentSize().width / 2.0f,
                           _background->getContentSize().height * 0.3f);
    _background->addChild(_strLabel, GameWinLayerDrawingOrderOthers);
    return true;
}

void GameWinLayer::setString(std::string stringLabel) {
    _strLabel->setString(stringLabel);
}

void GameWinLayer::setStars(int starNumber) {
    if (starNumber > 0) {
        _starVector.at(0)->setSpriteFrame("game_win_star_active.png");
        if (starNumber > 1) {
            _starVector.at(1)->setSpriteFrame("game_win_star_active.png");
            if (starNumber > 2) {
                _starVector.at(2)->setSpriteFrame("game_win_star_active.png");
                
            }
        }
    }
}

Size GameWinLayer::getLayerContentSize() {
    return _background->getContentSize();
}


void GameWinLayer::onMenu(Ref* sender) {
    log("GameWinLayer onMenu");
    Sound::getInstance()->playClick();
    GameData::getInstance()->setReturnToGame(true);
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.3f, SelectLevelScene::createScene(), true));
}

void GameWinLayer::onRestart(Ref* sender) {
    log("GameWinLayer onRestart");
    Sound::getInstance()->playRestartLevel();
    GameData::getInstance()->loadLevel();
    GameData::getInstance()->saveGame();
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.3f, GameScene::createScene(), true));
}

void GameWinLayer::onNextlevel(Ref* sender) {
    log("GameWinLayer onNextlevel");
    GameData::getInstance()->setLevel(GameData::getInstance()->getLevel() + 1);
    GameData::getInstance()->loadLevel();
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.3f, GameScene::createScene(), true));
}


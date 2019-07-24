#include "GameWarningLayer.h"
#include "Sound.h"
#include "GameData.h"
#include "GameScene.h"
#include "SelectLevelScene.h"

// on "init" you need to initialize your instance
bool GameWarningLayer::init()
{
    if ( !Layer::init() ) {
        return false;
    }
    
    // background
    _background = Sprite::createWithSpriteFrameName("game_warning_bg.png");
    this->addChild(_background, GameWarningLayerDrawingOrderBackground);
    
    // top menu
    auto close = MenuItemSprite::create(Sprite::createWithSpriteFrameName("game_warning_no.png"),
                                        Sprite::createWithSpriteFrameName("game_warning_no.png"),
                                        CC_CALLBACK_1(GameWarningLayer::onClose, this));
    close->setPosition(_background->getContentSize().width / 2.0f - close->getContentSize().width,
                       close->getContentSize().width * 0.3f);
    
    auto restart = MenuItemSprite::create(Sprite::createWithSpriteFrameName("game_win_restart.png"),
                                          Sprite::createWithSpriteFrameName("game_win_restart.png"),
                                          CC_CALLBACK_1(GameWarningLayer::onRestart, this));
    restart->setPosition(_background->getContentSize().width / 2 + close->getContentSize().width,
                         close->getContentSize().width * 0.3f);
    auto top_menu = Menu::create(close, restart, NULL);
    top_menu->setPosition(Vec2::ZERO);
    _background->addChild(top_menu, GameWarningLayerDrawingOrderOthers);
    
    _strLabel = Label::createWithBMFont("fonts/carterone-40-white.fnt", "");
    _strLabel->setDimensions(_background->getContentSize().width * 0.8f, _background->getContentSize().height *0.8f);
    _strLabel->setPosition(_background->getContentSize().width / 2.0f,
                           _background->getContentSize().height * 0.5f);
    _background->addChild(_strLabel, GameWarningLayerDrawingOrderOthers);
    return true;
}

void GameWarningLayer::setString(std::string stringLabel) {
    _strLabel->setString(stringLabel);
}

Size GameWarningLayer::getLayerContentSize() {
    return _background->getContentSize();
}


void GameWarningLayer::onClose(Ref* sender) {
    log("GameWarningLayer onMenu");
    Sound::getInstance()->playClick();
    this->removeFromParent();
}

void GameWarningLayer::onRestart(Ref* sender) {
    log("GameWarningLayer onRestart");
    Sound::getInstance()->playRestartLevel();
    GameData::getInstance()->loadLevel();
    GameData::getInstance()->saveGame();
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.3f, GameScene::createScene(), true));
}

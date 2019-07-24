#include "WarningLayer.h"
#include "Sound.h"
#include "GameData.h"
#include "GameScene.h"
#include "SelectLevelScene.h"

// on "init" you need to initialize your instance
bool WarningLayer::init()
{
    if ( !Layer::init() ) {
        return false;
    }
    
    // set up the reset layer
    _resetLayer = LayerColor::create(Color4B(0, 0, 0, 192));

    // add the reset layer
    this->addChild(_resetLayer, WarningLayerDrawingOrderLayer);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [&](Touch* touch, Event* event){
        return true;
    };
    listener->setSwallowTouches(true);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    
    // background
    auto visibleSize = Director::getInstance()->getVisibleSize();
    _background = Sprite::createWithSpriteFrameName("game_warning_bg.png");
    _background->setPosition(visibleSize.width / 2.0f,
                             visibleSize.height / 2.0f);
    this->addChild(_background, WarningLayerDrawingOrderBackground);
    
    // top menu
    auto close = MenuItemSprite::create(Sprite::createWithSpriteFrameName("game_warning_no.png"),
                                        Sprite::createWithSpriteFrameName("game_warning_no.png"),
                                        CC_CALLBACK_1(WarningLayer::onClose, this));
    close->setPosition(_background->getContentSize().width / 2.0f - close->getContentSize().width,
                       close->getContentSize().width * 0.3f);
    
    auto confirm = MenuItemSprite::create(Sprite::createWithSpriteFrameName("game_warning_yes.png"),
                                          Sprite::createWithSpriteFrameName("game_warning_yes.png"),
                                          CC_CALLBACK_1(WarningLayer::onConfirm, this));
    confirm->setPosition(_background->getContentSize().width / 2 + close->getContentSize().width,
                         close->getContentSize().width * 0.3f);
    auto top_menu = Menu::create(close, confirm, NULL);
    top_menu->setPosition(Vec2::ZERO);
    _background->addChild(top_menu, WarningLayerDrawingOrderOthers);
    
    _strLabel = Label::createWithBMFont("fonts/carterone-40-white.fnt", "");
    _strLabel->setDimensions(_background->getContentSize().width * 0.8f,
                             _background->getContentSize().height * 0.8f);
    _strLabel->setPosition(_background->getContentSize().width / 2.0f,
                           _background->getContentSize().height * 0.5f);
    _background->addChild(_strLabel, WarningLayerDrawingOrderOthers);
    return true;
}

void WarningLayer::setString(std::string stringLabel) {
    _strLabel->setString(stringLabel);
}

Size WarningLayer::getLayerContentSize() {
    return _background->getContentSize();
}


void WarningLayer::onClose(Ref* sender) {
    log("WarningLayer onClose");
    Sound::getInstance()->playClick();
    _resetLayer->removeFromParent();
    this->removeFromParent();
}

void WarningLayer::onConfirm(Ref* sender) {
    log("WarningLayer onConfirm");
    Sound::getInstance()->playClick();
    
    // delete saved game
    GameData::getInstance()->deleteSavedGame();
    
    // reset all levels
    Levels::getInstance()->reset();
    
    // reset all achievements
//    Achievements::getInstance()->reset();
    _resetLayer->removeFromParent();
    this->removeFromParent();
}

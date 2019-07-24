#include "OptionsScene.h"
#include "Sound.h"
#include "GameData.h"
#include "Options.h"
#include "Levels.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "Achievements.h"

Scene* OptionsScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = OptionsScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool OptionsScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    _resetLayerUp = false;
    
    // background
    auto background = Sprite::createWithSpriteFrameName("options_background.png");
    background->setPosition(160, 240);
    this->addChild(background, OptionsSceneDrawingOrderBackground);
    
    // options
    _soundOn = Sprite::createWithSpriteFrameName("options_sound_on.png");
    _soundOn->setPosition(160, 332);
    _soundOff = Sprite::createWithSpriteFrameName("options_sound_off.png");
    _soundOff->setPosition(160, 332);
    _musicOn = Sprite::createWithSpriteFrameName("options_music_on.png");;
    _musicOn->setPosition(160, 276);
    _musicOff = Sprite::createWithSpriteFrameName("options_music_off.png");
    _musicOff->setPosition(160, 276);
    _shakeOn = Sprite::createWithSpriteFrameName("options_shake_on.png");
    _shakeOn->setPosition(160, 220);
    _shakeOff = Sprite::createWithSpriteFrameName("options_shake_off.png");;
    _shakeOff->setPosition(160, 220);
    this->updateOptions();
    this->addChild(_soundOn, OptionsSceneDrawingOrderButton);
    this->addChild(_soundOff, OptionsSceneDrawingOrderButton);
    this->addChild(_musicOn, OptionsSceneDrawingOrderButton);
    this->addChild(_musicOff, OptionsSceneDrawingOrderButton);
    this->addChild(_shakeOn, OptionsSceneDrawingOrderButton);
    this->addChild(_shakeOff, OptionsSceneDrawingOrderButton);
    
    // reset data
    if (!GameData::getInstance()->getReturnToGame()) {
        auto reset = MenuItemSprite::create(Sprite::createWithSpriteFrameName("options_reset.png"),
                                            Sprite::createWithSpriteFrameName("options_reset2.png"),
                                            CC_CALLBACK_1(OptionsScene::onReset, this));
        auto resetMenu = Menu::create(reset, NULL);
        resetMenu->setPosition(160, 104);
        this->addChild(resetMenu, OptionsSceneDrawingOrderButton);
    }
    
    // back to menu or game
    MenuItemSprite* back;
    if (GameData::getInstance()->getReturnToGame()) {
        back = MenuItemSprite::create(Sprite::createWithSpriteFrameName("options_back_game.png"),
                                      Sprite::createWithSpriteFrameName("options_back_game2.png"),
                                      CC_CALLBACK_1(OptionsScene::onBack, this));
    } else {
        back = MenuItemSprite::create(Sprite::createWithSpriteFrameName("options_back_menu.png"),
                                      Sprite::createWithSpriteFrameName("options_back_menu2.png"),
                                      CC_CALLBACK_1(OptionsScene::onBack, this));
    }
    auto backMenu = Menu::create(back, NULL);
    backMenu->setPosition(160, 28);
    this->addChild(backMenu, OptionsSceneDrawingOrderButton);

    return true;
}


void OptionsScene::onReset(Ref* sender) {
    if (_resetLayerUp) return;
    
    log("OptionsScene onReset");
    Sound::getInstance()->playClick();
    _resetLayerUp = true;
    
    // set up the reset layer
    _resetLayer = LayerColor::create(Color4B(0, 0, 0, 192));
    
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // the background
    auto background = Sprite::createWithSpriteFrameName("options_reset_confirm_background.png");
    background->setPosition(visibleSize.width / 2,
                            visibleSize.height / 2);
    this->addChild(background, OptionsSceneDrawingOrderBackground);
    
    // the menu
    auto yes = MenuItemSprite::create(Sprite::createWithSpriteFrameName("options_reset_confirm_yes.png"),
                                      Sprite::createWithSpriteFrameName("options_reset_confirm_yes2.png"),
                                      CC_CALLBACK_1(OptionsScene::onResetConfirmYes, this));
    auto cancel = MenuItemSprite::create(Sprite::createWithSpriteFrameName("options_reset_confirm_cancel.png"),
                                           Sprite::createWithSpriteFrameName("options_reset_confirm_cancel2.png"),
                                          CC_CALLBACK_1(OptionsScene::onResetConfirmCancel, this));
    auto menu = Menu::create(yes, cancel, NULL);
    menu->setPosition(160, 221);
    _resetLayer->addChild(menu);
    
    // add the reset layer
    this->addChild(_resetLayer);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(OptionsScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(OptionsScene::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    

}

void OptionsScene::onBack(Ref* sender) {
    log("OptionsScene onBack");
    Sound::getInstance()->playClick();
    if (GameData::getInstance()->getReturnToGame()) {
        Options::getInstance()->load();
        Director::getInstance()->replaceScene(TransitionPageTurn::create(0.3f, GameScene::createScene(), true));
    } else {
        Director::getInstance()->replaceScene(TransitionPageTurn::create(0.3f, MenuScene::createScene(), true));
    }
}

void OptionsScene::onResetConfirmYes(Ref* sender) {
    log("OptionsScene onResetConfirmYes");
    Sound::getInstance()->playClick();
    
    // delete saved game
    GameData::getInstance()->deleteSavedGame();
    
    // reset all levels
    Levels::getInstance()->reset();
    
    // reset all achievements
    Achievements::getInstance()->reset();
    
    this->removeChild(_resetLayer);
    _resetLayerUp = false;
}

void OptionsScene::onResetConfirmCancel(Ref* sender) {
    log("OptionsScene onResetConfirmCancel");
    Sound::getInstance()->playClick();
    this->removeChild(_resetLayer);
    _resetLayerUp = false;
}

void OptionsScene::updateOptions() {
    if (Options::getInstance()->sound) {
        _soundOn->setOpacity(255);
        _soundOff->setOpacity(0);
    } else {
        _soundOn->setOpacity(0);
        _soundOff->setOpacity(255);
    }
    if (Options::getInstance()->music) {
        _musicOn->setOpacity(255);
        _musicOff->setOpacity(0);
    } else {
        _musicOn->setOpacity(0);
        _musicOff->setOpacity(255);
    }
    if (Options::getInstance()->shake) {
        _shakeOn->setOpacity(255);
        _shakeOff->setOpacity(0);
    } else {
        _shakeOn->setOpacity(0);
        _shakeOff->setOpacity(255);
    }
}


bool OptionsScene::onTouchBegan(Touch * touch, Event * event){
    return true;
}

void OptionsScene::onTouchEnded(Touch * touch, Event * event) {
    if (_resetLayerUp) return;
    Point location = this->convertTouchToNodeSpace(touch);
    
    auto soundRect = Rect(10, 340, 301, 56);
    auto musicRect = Rect(10, 248, 301, 56);
    auto shakeRect = Rect(10, 193, 301, 56);
    
    bool toggled = false;
    
    // sound?
    if (soundRect.containsPoint(location)) {
        Sound::getInstance()->playClick();
        if(Options::getInstance()->sound) {
            log("OptionsScene sound turned off");
            Options::getInstance()->sound = 0;
        } else {
            log("OptionsScene sound turned on");
            Options::getInstance()->sound = 1;
        }
        toggled = true;
    }
    
    // music?
    if (musicRect.containsPoint(location)) {
        Sound::getInstance()->playClick();
        if(Options::getInstance()->music) {
            log("OptionsScene music turned off");
            Sound::getInstance()->stopMusic();
            Options::getInstance()->music = 0;
        } else {
            log("OptionsScene music turned on");
            Options::getInstance()->music = 1;
            Sound::getInstance()->startMusicMenu();
        }
        toggled = true;
    }
    
    // shake?
    if (shakeRect.containsPoint(location)) {
        Sound::getInstance()->playClick();
        if(Options::getInstance()->shake) {
            log("OptionsScene shake turned off");
            Options::getInstance()->shake = 0;
        } else {
            log("OptionsScene shake turned on");
            Options::getInstance()->shake = 1;
        }
        toggled = true;
    }
    
    if(toggled) {
        this->updateOptions();
        Options::getInstance()->save();
    }
}



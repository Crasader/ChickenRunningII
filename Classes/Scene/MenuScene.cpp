#include "MenuScene.h"
#include "Sound.h"
#include "GameData.h"
#include "MapScene.h"
#include "InstructionsScene.h"
#include "OptionsScene.h"
#include "AchievementsScene.h"
#include "MapScene.h"
#include "ExtensibleSettingButton.h"
#include "WarningLayer.h"
#include "SonarFrameworks.h"

USING_NS_CC;

#define MARGIN_BUTTON = 3.0f;

MenuScene::MenuScene() {}

MenuScene::~MenuScene() {
    SonarCocosHelper::AdMob::hideBannerAd();
}

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->initBackground();
    this->initSettingIcon();
    
    SonarCocosHelper::IOS::Setup();
    
//    SonarCocosHelper::AdMob::hideBannerAd();
//    SonarCocosHelper::AdMob::showBannerAd(SonarCocosHelper::AdBannerPosition::eBottom);
//    SonarCocosHelper::AdMob::preLoadFullscreenAd();
    return true;
}

void MenuScene::initBackground() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // background
    Sprite* background = Sprite::create("images/menu_background.png");
    background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(background, MenuSceneDrawingOrderBackground);

    // header
    auto header = Sprite::createWithSpriteFrameName("menu_header.png");
    header->setPosition(visibleSize.width / 2, visibleSize.height * 4 / 5);
    this->addChild(header, MenuSceneDrawingOrderOther);

    // role
    auto role = Sprite::createWithSpriteFrameName("menu_role.png");
    role->setPosition(visibleSize.width / 2,
                      header->getPosition().y - header->getContentSize().height / 2 - role->getContentSize().height / 2);
    this->addChild(role, MenuSceneDrawingOrderOther);
    
    // menu
    auto playMenuItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("menu_play.png"),
                                               Sprite::createWithSpriteFrameName("menu_play2.png"),
                                               CC_CALLBACK_1(MenuScene::onPlay, this));
    playMenuItem->setPosition(visibleSize.width / 2,
                              role->getPosition().y - role->getContentSize().height / 2 - playMenuItem->getContentSize().height / 2 - 10);
    
    auto instructionsMenuItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("menu_instructions.png"),
                                                       Sprite::createWithSpriteFrameName("menu_instructions2.png"),
                                                       CC_CALLBACK_1(MenuScene::onInstructions, this));
    instructionsMenuItem->setPosition(visibleSize.width / 2,
                                      playMenuItem->getPosition().y - playMenuItem->getContentSize().height - 2.0f);

    auto resetMenuItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("menu_reset.png"),
                                                  Sprite::createWithSpriteFrameName("menu_reset2.png"),
                                                  CC_CALLBACK_1(MenuScene::onReset, this));
    resetMenuItem->setPosition(visibleSize.width / 2,
                                 instructionsMenuItem->getPosition().y - instructionsMenuItem->getContentSize().height - 2.0f);

    
    auto menu = Menu::create(playMenuItem, instructionsMenuItem, resetMenuItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, MenuSceneDrawingOrderOther);
}

void MenuScene::initSettingIcon() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto settionIcon = ExtensibleSettingButton::create();
    settionIcon->setPosition(settionIcon->getExtensibleSettingButtonSize().width,
                                      visibleSize.height - settionIcon->getExtensibleSettingButtonSize().height);
    this->addChild(settionIcon, MenuSceneDrawingOrderOther);
}

void MenuScene::onPlay(Ref* pSender) {
    log("MenuScene onPlay");
    Sound::getInstance()->playClick();
    GameData::getInstance()->setReturnToGame(false);
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.3f, MapScene::createScene(), false));
}

void MenuScene::onInstructions(Ref* pSender) {
    log("MenuScene onInstructions");
    Sound::getInstance()->playClick();
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.3f, InstructionsScene::createScene(), false));
//    this->scheduleOnce(schedule_selector(MenuScene::showAdmobInterstitial), 3);
}

void MenuScene::onReset(Ref* pSender) {
    log("MenuScene onOptions");
    Sound::getInstance()->playClick();
    auto warning = WarningLayer::create();
    warning->setString("Confirm Reset Game?");
    this->addChild(warning, MenuSceneDrawingOrderLayer);
}

//void MenuScene::onAchievements(Ref* pSender) {
//    log("MenuScene onAchievements");
//    Sound::getInstance()->playClick();
//    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.3f, AchievementsScene::createScene(), false));
//}

void MenuScene::showAdmobInterstitial(float dt) {
//    // declare this flag in your program
//    bool AdPreloaded = false;
//    
//    // when you preload, change to this
//    if( AdPreloaded == false ) {
//        SonarCocosHelper::AdMob::preLoadFullscreenAd();
//        AdPreloaded = true;
//    }
//    
//    // when you show, change to this
//    SonarCocosHelper::AdMob::showPreLoadedFullscreenAd();
//    AdPreloaded = false;
    
    SonarCocosHelper::AdMob::showFullscreenAd();
}


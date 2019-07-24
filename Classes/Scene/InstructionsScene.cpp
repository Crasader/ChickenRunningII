#include "InstructionsScene.h"
#include "Helpers.h"
#include "Sound.h"
#include "MenuScene.h"
#include "InstructionLayer.h"

Scene* InstructionsScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = InstructionsScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool InstructionsScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->initBackground();
    this->initContent();
    
    return true;
}

void InstructionsScene::initContent() {
    auto layer = InstructionLayer::create();
    this->addChild(layer, InstructionsSceneDrawingOrderLayer);
}

void InstructionsScene::initBackground() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // background
    Sprite* background = Sprite::create("images/select_level_background.png");
    background->setPosition(visibleSize.width / 2,
                            visibleSize.height / 2);
    this->addChild(background, InstructionsSceneDrawingOrderBackground);
    
    // header
    auto header = Sprite::createWithSpriteFrameName("instructions_header.png");
    header->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    header->setPosition(visibleSize.width / 2,
                        visibleSize.height );
    this->addChild(header, InstructionsSceneDrawingOrderOthers);
    
    // back menu
    auto backItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("select_level_back.png"),
                                           Sprite::createWithSpriteFrameName("select_level_back2.png"),
                                           CC_CALLBACK_1(InstructionsScene::onBack, this));
    backItem->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    backItem->setPosition(visibleSize.width * 0.05f,
                          visibleSize.height * 0.1f);
    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, InstructionsSceneDrawingOrderOthers);
}

void InstructionsScene::onBack(Ref* sender) {
    log("InstructionsScene onBack");
    Sound::getInstance()->playClick();
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.3f, MenuScene::createScene(), true));
}

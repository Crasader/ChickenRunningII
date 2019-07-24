//
//  LevelListLayer.cpp
//  HuaRong
//
//  Created by kangbiao on 15/5/27.
//
//

#include "GameIntroLayer.h"

using namespace ui;

GameIntroLayer::GameIntroLayer()
{
    
}

GameIntroLayer::~GameIntroLayer() {
    
}

bool  GameIntroLayer::init() {
    if ( ! Layer::init() )
    {
        return false;
    }
    
    // set up the reset layer
    auto resetLayer = LayerColor::create(Color4B(0, 0, 0, 192));
    
    // add the reset layer
    this->addChild(resetLayer, GameIntroLayerDrawingOrderColorLayer);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameIntroLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameIntroLayer::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    this->initIntroOthers();
    
    return true;
}

void GameIntroLayer::initIntroOthers() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto tipsMenu = Sprite::createWithSpriteFrameName("game_tips_menu.png");
    tipsMenu->setPosition(Vec2(visibleSize.width * 0.2f, visibleSize.height * 0.88f));
    this->addChild(tipsMenu, GameIntroLayerDrawingOrderTips);
    
    auto tipsLevel = Sprite::createWithSpriteFrameName("game_tips_level.png");
    tipsLevel->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.88f));
    this->addChild(tipsLevel, GameIntroLayerDrawingOrderTips);

    auto tipsStep = Sprite::createWithSpriteFrameName("game_tips_step.png");
    tipsStep->setPosition(Vec2(visibleSize.width * 0.8f, visibleSize.height * 0.88f));
    this->addChild(tipsStep, GameIntroLayerDrawingOrderTips);

    auto tipsMain = Sprite::createWithSpriteFrameName("game_tips_intro.png");
    tipsMain->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
    this->addChild(tipsMain, GameIntroLayerDrawingOrderTips);

}

#pragma mark - for init function

bool GameIntroLayer::onTouchBegan(Touch * touch, Event *event) {
    return true;
}

void GameIntroLayer::onTouchEnded(Touch * touch, Event *event) {
    this->removeFromParent();
}
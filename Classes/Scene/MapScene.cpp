#include "MapScene.h"
#include "GameData.h"
#include "Sound.h"
#include "MapIcon.h"
#include "SelectLevelScene.h"
#include "MenuScene.h"
#include "SonarFrameworks.h"

Scene* MapScene::sceneWithStage(int stage) {
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MapScene::create();

    layer->highlight(stage);
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


Scene* MapScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MapScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MapScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    SonarCocosHelper::AdMob::hideBannerAd();
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // background
    auto background = Sprite::create("images/map_background.png");
    background->setPosition(visibleSize.width / 2,
                            visibleSize.height / 2);
    this->addChild(background, MapSceneDrawingOrderBackground);
    
    // header
    auto header = Sprite::createWithSpriteFrameName("map_header.png");
    header->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    header->setPosition(visibleSize.width / 2,
                        visibleSize.height );
    this->addChild(header, MapSceneDrawingOrderOther);
    
    // footer
    auto foot = Sprite::createWithSpriteFrameName("map_footprints.png");
    foot->setPosition(visibleSize.width / 2,
                      visibleSize.height * 0.5f );
    this->addChild(foot, MapSceneDrawingOrderFootPrint);

    // back menu
    auto backItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("select_level_back.png"),
                                           Sprite::createWithSpriteFrameName("select_level_back2.png"),
                                           CC_CALLBACK_1(MapScene::onBack, this));
    backItem->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    backItem->setPosition(visibleSize.width * 0.05f,
                          visibleSize.height * 0.1f);
    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    // the key and locks
    _stageLocked1 = false;
    _stageLocked2 = GameData::getInstance()->stageLocked(GameStage2);
    _stageLocked3 = GameData::getInstance()->stageLocked(GameStage3);
    _stageLocked4 = GameData::getInstance()->stageLocked(GameStage4);
    
    _forestPoint = Vec2(visibleSize.width / 2,
                        visibleSize.height * 0.1f);
    _cavesPoint  = Vec2(visibleSize.width / 4.0f,
                        visibleSize.height * 0.35f);
    _beachPoint  = Vec2(visibleSize.width * 0.75f,
                        visibleSize.height * 0.60f);
    _shipPoint   = Vec2(visibleSize.width / 4.0f,
                        visibleSize.height * 0.80f);
    
    // forest
    auto stage1 = Sprite::createWithSpriteFrameName("map_stage_1.png");
    stage1->setPosition(_forestPoint);
    stage1->setRotation(-10.0f);
    stage1->runAction(RepeatForever::create(Sequence::create(RotateBy::create(0.5f, 20.0f),
                                                             RotateBy::create(0.5f, -20.0f),
                                                             NULL)));
    this->addChild(stage1, MapSceneDrawingOrderOther);
    
    // caves
    std::string filename;
    if (!_stageLocked2)
        filename = "map_stage_2.png";
    else
        filename = "map_lock.png";
    
    auto stage2 = Sprite::createWithSpriteFrameName(filename);
    stage2->setPosition(_cavesPoint);
    stage2->setRotation(-10.0f);
    stage2->runAction(RepeatForever::create(Sequence::create(RotateBy::create(0.5f, 20.0f),
                                                             RotateBy::create(0.5f, -20.0f),
                                                             NULL)));
    this->addChild(stage2, MapSceneDrawingOrderOther);
    
    // beach
    if(!_stageLocked3)
        filename = "map_stage_3.png";
    else
        filename = "map_lock.png";
    
    auto beach = Sprite::createWithSpriteFrameName(filename);
    beach->setPosition(_beachPoint);
    beach->setRotation(-10.0f);
    beach->runAction(RepeatForever::create(Sequence::create(RotateBy::create(0.5f, 20.0f),
                                                            RotateBy::create(0.5f, -20.0f),
                                                            NULL)));
    this->addChild(beach, MapSceneDrawingOrderOther);

    // pirate ship
    if(!_stageLocked4)
        filename = "map_stage_4.png";
    else
        filename = "map_lock.png";
    
    auto ship = Sprite::createWithSpriteFrameName(filename);
    ship->setPosition(_shipPoint);
    ship->setRotation(-10.0f);
    ship->runAction(RepeatForever::create(Sequence::create(RotateBy::create(0.5f, 20.0f),
                                                           RotateBy::create(0.5f, -20.0f),
                                                            NULL)));
    this->addChild(ship, MapSceneDrawingOrderOther);

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(MapScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(MapScene::onTouchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

bool MapScene::onTouchBegan(Touch* touch, Event* event) {
    log("MapScene onTouchBegan");
    return true;
}
void MapScene::onTouchEnd(Touch* touch, Event* event) {
    log("MapScene onTouchEnd");
    auto touchEnd = this->convertTouchToNodeSpace(touch);
    
    // calculate distances
    float forestDistance = touchEnd.distance(_forestPoint);
    float cavesDistance  = touchEnd.distance(_cavesPoint);
    float beachDistance  = touchEnd.distance(_beachPoint);
    float shipDistance   = touchEnd.distance(_shipPoint);
    
    // set the stage
    if(forestDistance < cavesDistance && forestDistance < beachDistance && forestDistance < shipDistance)
        GameData::getInstance()->setStageNumber(GameStage1);
    else if(cavesDistance < forestDistance && cavesDistance < beachDistance && cavesDistance < shipDistance)
        GameData::getInstance()->setStageNumber(GameStage2);
    else if(beachDistance < forestDistance && beachDistance < cavesDistance && beachDistance < shipDistance)
        GameData::getInstance()->setStageNumber(GameStage3);
    else
        GameData::getInstance()->setStageNumber(GameStage4);
    
    // if the selected stage is unlocked
    if((GameData::getInstance()->getStage() == GameStage1 && !_stageLocked1) ||
       (GameData::getInstance()->getStage() == GameStage2 && !_stageLocked2) ||
       (GameData::getInstance()->getStage() == GameStage3 && !_stageLocked3) ||
       (GameData::getInstance()->getStage() == GameStage4 && !_stageLocked4)) {
        
        // redirect to select level scene
        Sound::getInstance()->playClick();
        
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, SelectLevelScene::createScene()));
    } else {
        // map locked sound
        Sound::getInstance()->playMapLocked();
    }
}

void MapScene::highlight(int stage) {
    // highlight?
    Point point;
    switch(stage) {
        default: point = nullptr; break;
        case GameStage1: point = _forestPoint; break;
        case GameStage2: point = _cavesPoint; break;
        case GameStage3: point = _beachPoint; break;
        case GameStage4: point = _shipPoint; break;
    }
    if (point != nullptr) {
        auto emitter = ParticleFlower::create();
        emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("map_sparkle.png"));
        emitter->setPosition(point);
        emitter->setEmissionRate(10.0f);
        emitter->setTotalParticles(30);
        emitter->setSpeed(50);
        emitter->setSpeedVar(50.0f);
        emitter->setStartColor(Color4F(1, 1, 1, 0.3));
        emitter->setStartColorVar(Color4F(0.2, 0.2, 0.2, 0.5));
        this->addChild(emitter);
    }
}

void MapScene::onBack(Ref* sender) {
    log("SelectLevelScene onBack");
    Sound::getInstance()->playClick();
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.3f, MenuScene::createScene(), true));
}


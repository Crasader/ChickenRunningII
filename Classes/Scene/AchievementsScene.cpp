#include "AchievementsScene.h"
#include "Sound.h"
#include "Achievements.h"
#include "MenuScene.h"
#include "Helpers.h"

Scene* AchievementsScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = AchievementsScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool AchievementsScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    log("AchievementsScene init");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    // background
    auto background = Sprite::createWithSpriteFrameName("achievements_background.png");
    background->setPosition(visibleSize.width / 2,
                            visibleSize.height / 2);
    this->addChild(background, AchievementsSceneDrawingOrderBackground);
    
    // menu
    _back = MenuItemSprite::create(Sprite::createWithSpriteFrameName("achievements_back.png"),
                                       Sprite::createWithSpriteFrameName("achievements_back2.png"),
                                       CC_CALLBACK_1(AchievementsScene::onBack, this));
    _back->setOpacity(64);
    _next = MenuItemSprite::create(Sprite::createWithSpriteFrameName("achievements_next.png"),
                                       Sprite::createWithSpriteFrameName("achievements_next2.png"),
                                       CC_CALLBACK_1(AchievementsScene::onNext, this));
    auto backToMenu = MenuItemSprite::create(Sprite::createWithSpriteFrameName("achievements_menu.png"),
                                             Sprite::createWithSpriteFrameName("achievements_menu2.png"),
                                             CC_CALLBACK_1(AchievementsScene::onMenu, this));
    auto menu = Menu::create(_back, backToMenu, _next, NULL);
    menu->setPosition(160, 28.5);
    this->addChild(menu, AchievementsSceneDrawingOrderBackground);
    
    // pages
    _pageNumber = 1;
    _numPages = (int) (Achievements::getInstance()->getNumAchievements() / 5);
    if (Achievements::getInstance()->getNumAchievements() % 5 > 0)
        _numPages++;
    _pageLayer = Layer::create();
    this->addChild(_pageLayer);
    
    // display achievements
    for(int  i=0; i< Achievements::getInstance()->getNumAchievements(); i++) {
        int page = (int)(i / 5);
        int y = 4 - (i % 5);
        
        std::string topText = Achievements::getInstance()->getName(i);
        std::string bottomText = Achievements::getInstance()->getDescription(i);
        
        // shadow
        auto achievement_shadow = Sprite::createWithSpriteFrameName("achievements_shadow.png");
        achievement_shadow->setPosition(160+320*page, 92+68*y);
        this->addChild(achievement_shadow);
        
        // text
        auto achievment_label_top = Label::createWithSystemFont(topText, "arial.ttf", 29.0f);
        achievment_label_top->setPosition(194+320*page, 107+68*y);
        this->addChild(achievment_label_top);
        auto achievment_label_bottom = Label::createWithSystemFont(bottomText, "arial.ttf", 22.0f);
        achievment_label_bottom->setPosition(194+320*page, 81+68*y);
        this->addChild(achievment_label_bottom);
        
        if (Achievements::getInstance()->getAchieved().at(i) == 1) {
            // achieved
            auto achievement_trophy = Sprite::createWithSpriteFrameName("achievements_trophy.png");
            achievement_trophy->setPosition(44+320*page, 92+68*y);
            this->addChild(achievement_trophy);
        } else {
            // have not yet achieved
            auto achievement_trophy_locked = Sprite::createWithSpriteFrameName("achievements_trophy_locked.png");
            achievement_trophy_locked->setPosition(44+320*page, 92+68*y);
            this->addChild(achievement_trophy_locked);
            
            // fade the text
            achievment_label_top->setOpacity(192);
            achievment_label_bottom->setOpacity(192);
        }
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(AchievementsScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(AchievementsScene::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void AchievementsScene::onBack(Ref* sender) {
    log("AchievementsScene onBack");
    Sound::getInstance()->playClick();
    this->moveBack();
}

void AchievementsScene::onNext(Ref* sender) {
    log("AchievementsScene onNext");
    Sound::getInstance()->playClick();
    this->moveNext();
}

void AchievementsScene::onMenu(Ref* sender) {
    log("AchievementsScene onMenu");
    Sound::getInstance()->playClick();
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.3f, MenuScene::createScene(), true));
}

void AchievementsScene::moveBack() {
    if(_pageNumber > 1) {
        _pageNumber--;
        if (_pageNumber == 1)
            _back->setOpacity(64);
        _next->setOpacity(255);
        this->scroll();
    }

}

void AchievementsScene::moveNext() {
    if (_pageNumber < _numPages) {
        _pageNumber++;
        if(_pageNumber == _numPages)
            _next->setOpacity(64);
        _back->setOpacity(255);
        this->scroll();
    }

}

void AchievementsScene::scroll() {
    float x = (_pageNumber-1)*-320;
    _pageLayer->runAction(MoveTo::create(0.2f, Vec2(x, 0)));

}


//- (void) registerWithTouchDispatcher {
//    [[CCTouchDispatcher sharedDispatcher] addTargetedDelegate:self priority:0 swallowsTouches:YES];
//}

bool AchievementsScene::onTouchBegan(Touch * touch, Event * event) {
    _touchStart = this->convertTouchToNodeSpace(touch);
    return true;
}

void AchievementsScene::onTouchEnded(Touch * touch, Event * event) {
    Point touchEnd = this->convertTouchToNodeSpace(touch);
    
    switch (Helpers::swipeDirection(_touchStart, touchEnd)) {
        case GameDirLeft:
            Sound::getInstance()->playKeyMove();
            this->moveNext();
            break;
        case GameDirRight:
            Sound::getInstance()->playKeyMove();
            this->moveBack();
            break;
    }
}



#include "LevelSelect.h"
#include "GameScene.h"
#include "Sound.h"
#include "GameData.h"
#include "ui/CocosGUI.h"

using namespace ui;

LevelSelect * LevelSelect::create(int level, int pageIndex) {
    auto pRet = new LevelSelect();
    
    if (pRet->init(level, pageIndex)) {
        pRet->autorelease();
    } else {
        delete pRet;
        return nullptr;
    }
    
    return pRet;
}

bool  LevelSelect::init(int level, int pageIndex) {
    if ( !Sprite::init() ) {
        return false;
    }
    _level = level;
    _levelStatus = LevelStatusActive;
    _starNumber = 0;
    _pageIndex  = pageIndex;
    this->initBackground();
    
    return true;
}

void LevelSelect::initBackground() {
    _background = Sprite::createWithSpriteFrameName("level_bg_active.png");

    auto levelItem = MenuItemImage::create();
    levelItem->setNormalImage(_background);
    levelItem->setSelectedImage(_background);
    levelItem->setCallback(CC_CALLBACK_1(LevelSelect::onTouchClickCallBack, this));
    levelItem->setPosition(Vec2::ZERO);
    
    auto skillMenu = Menu::create(levelItem, NULL);
    skillMenu->setPosition(Vec2::ZERO);
    this->addChild(skillMenu, LevelSelectDrawingOrderBackground);
    
    
    auto numberLabel = Label::createWithBMFont("fonts/carterone-40-white.fnt", StringUtils::format("%d", _level));
    numberLabel->setPosition(_background->getContentSize().width / 2.0f,
                             _background->getContentSize().height * 0.6f);
    _background->addChild(numberLabel);
    
    for (int i = 0; i < STAR_NUMBER; i++) {
        auto starSprite = Sprite::createWithSpriteFrameName("level_star_inactive.png");
        starSprite->setPosition(_background->getContentSize().width / 2.0f - starSprite->getContentSize().width * (1.0f - i),
                                _background->getContentSize().height * 0.3f);

        _starVector.pushBack(starSprite);
        _background->addChild(starSprite);
    }
}

void LevelSelect::setLevelStatus(unsigned int levelStatus, int starNumber) {
    _levelStatus = levelStatus;
    _starNumber  = starNumber;
    
    switch (levelStatus) {
        case LevelStatusActive: {
            _background->setSpriteFrame("level_bg_active.png");
            if (starNumber == 0) {
                for (int i = 0; i < STAR_NUMBER; i++) {
                    _starVector.at(i)->setSpriteFrame("level_star_inactive.png");
                }
            }
            if (starNumber > 0) {
                _starVector.at(0)->setSpriteFrame("level_star_active.png");
                if (starNumber > 1) {
                    _starVector.at(1)->setSpriteFrame("level_star_active.png");
                    if (starNumber > 2) {
                        _starVector.at(2)->setSpriteFrame("level_star_active.png");
                        
                    }
                }
            }
        }
            break;
            
        case LevelStatusInactive: {
            _background->setSpriteFrame("level_bg_inactive.png");
            for (int i = 0; i < STAR_NUMBER; i++) {
                _starVector.at(i)->setSpriteFrame("level_star_disable.png");
            }
        }
            break;
    }
}

Size LevelSelect::getLevelContentSize() {
    return this->_background->getContentSize();
}


void LevelSelect::onTouchClickCallBack(Ref* pSender) {
    auto pageView = static_cast<PageView*>( this->getParent()->getParent()->getParent()->getParent());
    int currentIndex = pageView->getCurPageIndex();

    if (_levelStatus == LevelStatusActive && currentIndex == _pageIndex) {
        log("LevelSelect onTouchClickCallBack:: level: %d", _level);
        // change music
            Sound::getInstance()->startMusicGameplay();
        
            // load level, start game
            GameData::getInstance()->setLevel(_level);
            GameData::getInstance()->loadLevel();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameScene::createScene()));
    }
}
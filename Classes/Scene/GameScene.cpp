#include "GameScene.h"
#include "GameData.h"
#include "GameTile.h"
#include "Options.h"
#include "Achievements.h"
#include "GameMenuLayer.h"
#include "MenuScene.h"
#include "MapScene.h"
#include "SelectLevelScene.h"
#include "Helpers.h"
#include "GameWinLayer.h"
#include "GameWarningLayer.h"
#include "SonarFrameworks.h"
#include "GameIntroLayer.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
//    SonarCocosHelper::AdMob::hideBannerAd();
}

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    
    // set the game as active
    GameData::getInstance()->setActiveGame(true);

    // start the level
    this->restartLevel();
    
    return true;
}

void GameScene::setCurrentGame() {
    // let the applicatin know who's in charge
//    SkeletonKeyAppDelegate* delegate = ((SkeletonKeyAppDelegate*)([UIApplication sharedApplication].delegate));
//    delegate.currentGame = self;
}
void GameScene::unsetCurrentGame() {
    // stop letting the applicatin know who's in charge
//    SkeletonKeyAppDelegate* delegate = ((SkeletonKeyAppDelegate*)([UIApplication sharedApplication].delegate));
//    delegate.currentGame = nil;
}


void GameScene:: restartLevel() {
    // in case we've already been playing
    this->removeAllChildren();
    this->setCurrentGame();
    
    // background
    auto background = Sprite::create("images/select_level_background.png");
    background->setPosition(_visibleSize.width / 2,
                            _visibleSize.height / 2);
    this->addChild(background, GameSceneDrawingOrderBackground);
//    NSString* backgroundFilename;
//    switch(gameData.stage) {
//        case GameStageForest: backgroundFilename = @"game_background_forest.png"; break;
//        case GameStageCaves:  backgroundFilename = @"game_background_caves.png";  break;
//        case GameStageBeach:  backgroundFilename = @"game_background_beach.png";  break;
//        case GameStageShip:	  backgroundFilename = @"game_background_ship.png";   break;
//    }
//    background = [CCSprite spriteWithFile:backgroundFilename];


    // menu button
    auto backItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("game_back.png"),
                                           Sprite::createWithSpriteFrameName("game_back2.png"),
                                           CC_CALLBACK_1(GameScene::onBack, this));
    backItem->setPosition(_visibleSize.width * 0.01f + backItem->getContentSize().width / 2.0f,
                          _visibleSize.height * 0.99f - backItem->getContentSize().height / 2.0f);
    auto menuItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("game_menu.png"),
                                           Sprite::createWithSpriteFrameName("game_menu2.png"),
                                           CC_CALLBACK_1(GameScene::onMenu, this));
    menuItem->setPosition(backItem->getPosition().x + menuItem->getContentSize().width + 10.0f,
                          _visibleSize.height * 0.99f - backItem->getContentSize().height / 2.0f);
    auto menu = Menu::create(backItem, menuItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, GameSceneDrawingOrderMenuAndLabel);
    
    // heads up display
    auto levelBg = Sprite::createWithSpriteFrameName("game_level_bg.png");
    levelBg->setPosition(_visibleSize.width * 0.5f,
                         _visibleSize.height * 0.99f - backItem->getContentSize().height / 2.0f);
    this->addChild(levelBg, GameSceneDrawingOrderMenuAndLabel);
    auto level = Label::createWithBMFont("fonts/carterone-40-white.fnt", StringUtils::format("%d", GameData::getInstance()->getLevel()));
    level->setPosition(levelBg->getContentSize().width * 0.6f,
                       levelBg->getContentSize().height / 2.0f);
    levelBg->addChild(level);
    
    
    _stepBg = Sprite::createWithSpriteFrameName("game_step_bg.png");
    _stepBg->setPosition(_visibleSize.width * 0.8f,
                         _visibleSize.height * 0.99f - backItem->getContentSize().height / 2.0f);
    this->addChild(_stepBg, GameSceneDrawingOrderMenuAndLabel);
    auto moves = Label::createWithBMFont("fonts/carterone-40-white.fnt", StringUtils::format("%d/%d", GameData::getInstance()->getStepNumber(), GameData::getInstance()->getMinStepNumber()));
    moves->setPosition(_stepBg->getContentSize().width * 0.9f,
                       _stepBg->getContentSize().height / 2.0f);
    moves->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    moves->setTag(GameTagMoves);
    _stepBg->addChild(moves);
    
    // the frame
    _tileLayer = Layer::create();
    Sprite* tileBackground = Sprite::createWithSpriteFrameName("game_play_background.png");
    tileBackground->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _tileLayer->setPosition(_visibleSize.width / 2.0f - tileBackground->getContentSize().width / 2.0f,
                            _visibleSize.height / 7);
    this->addChild(_tileLayer, GameSceneDrawingOrderTileBackgound);
    _tileLayer->addChild(tileBackground, GameSceneDrawingOrderTileBackgound);
    // draw the tiles
    int x,y;
    GameTile* tile;
    for (x = 0; x < GAME_BOARD_WIDTH; x++) {
        for (y = 0; y < GAME_BOARD_HEIGHT; y++) {
            int tileType = GameData::getInstance()->getTileType(x, y);
            if (tileType != GameTileSpace) {
                tile = GameTile::create(tileType, x, y);
                _tileLayer->addChild(tile, GameSceneDrawingOrderTile, GameTagTiles+(GAME_BOARD_WIDTH*y+x));
            }
        }
    }
    
    // draw the keys
    for(int i = 0; i < GameData::getInstance()->getKeys().size(); i++) {
        GameDataKey* key = GameData::getInstance()->getKeys().at(i);
        if (! key->getUsed()) {
            tile = GameTile::create(GameTileKey, key->getX(), key->getY());
            _tileLayer->addChild(tile, GameSceneDrawingOrderTile, GameTagKeys + i);
        }
    }
    
    // check for winning
    _won = false;
    
    // message
    if (GameData::getInstance()->getLevel() == 1) {
//        this->messageDisplay(GameMessageSwipeScreen);
        this->addIntroLayer();
    }
    
    // only save the game if a move has been made
    _firstMove = false;
    
    // achievements
    _isAchievementActive = false;
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, _tileLayer);
    
//#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    SonarCocosHelper::AdMob::showBannerAd(SonarCocosHelper::AdBannerPosition::eBottom);
//#endif
}

void GameScene::moveKeys(int dir) {
    if (_won) return;
    
    _firstMove = true;
    
//    int movesLeft = GameData::getInstance()->getMovesLeft();
//    if (movesLeft == 0) {
//        // out of moves, sorry
//        if (Options::getInstance()->shake) {
//            this->messageDisplay(GameMessageNoMovesShake);
//        } else {
//            this->messageDisplay(GameMessageNoMovesMenu);
//        }
//        return;
//    }
    
    // update moves left label?
    GameData::getInstance()->moveKeys(dir);
//    if (GameData::getInstance()->getDoorOpened()) {
        // achievement "Knock Knock"
//        this->unlockAchievement(AchievementKnockKnock);
//        Achievements::getInstance()->setDoorsOpened(Achievements::getInstance()->getDoorsOpened() + 1);
//        Achievements::getInstance()->save();
//        
//        // check for achievement "The Doorman"
//        if(Achievements::getInstance()->getDoorsOpened() == 50) {
//            this->unlockAchievement(AchievementTheDoorman);
//        }
//        
//        // check for achievement "The Door to Nowhere"
//        if(GameData::getInstance()->getLevel() == 85) {
//            this->unlockAchievement(AchievementTheDoorToKnowhere);
//        }
//    }
//    if (GameData::getInstance()->getMovesLeft() != movesLeft) {
        auto moves = (Label *) _stepBg->getChildByTag(GameTagMoves);
//        moves->setString(StringUtils::format("%d", GameData::getInstance()->getMovesLeft()));
        moves->setString(StringUtils::format("%d/%d", GameData::getInstance()->getStepNumber(), GameData::getInstance()->getMinStepNumber()));
//    }
    
    // update the tiles, keys
    for (int x2 = 0; x2 < GAME_BOARD_WIDTH; x2++) {
        for (int y2 = 0; y2 < GAME_BOARD_HEIGHT; y2++) {
            auto tile = (GameTile*) _tileLayer->getChildByTag(GameTagTiles+(GAME_BOARD_WIDTH*y2+x2));
            if (tile != nullptr) {
                int tileType = GameData::getInstance()->getTileType(x2, y2);
                if (tileType != tile->getTileType()) {
                    tile->changeType(tileType);
                }
            }
        }
    }
    // update the keys
    for (int i = 0; i < GameData::getInstance()->getKeys().size(); i++) {
        GameTile* tile = (GameTile*) _tileLayer->getChildByTag(GameTagKeys+i);
        if (tile != nullptr) {
            // if it's used now, remove it
            GameDataKey* key = (GameDataKey*) GameData::getInstance()->getKeys().at(i);
            if (key->getUsed()) {
                _tileLayer->removeChildByTag(GameTagKeys+i);
            } else {
                // if the key has moved, update it
                if (tile->getX() != key->getX() || tile->getY() != key->getY())
                    tile->changePosition(key->getX(), key->getY());
            }
        }
    }
    
    // check for a win
    bool checkForWin = true;
    for (int i=0; i < GameData::getInstance()->getKeys().size(); i++) {
        GameDataKey* key = (GameDataKey*) GameData::getInstance()->getKeys().at(i);
        if(key->getUsed() == false)
            checkForWin = false;
    }
    
    if (checkForWin) {
        _won = true;
        this->runAction(Sequence::create(DelayTime::create(0.01f),
                                         CallFunc::create(CC_CALLBACK_0(GameScene::onCompletedLevel, this)),
                                         NULL));
    } else {
        // check for stuck
        if (GameData::getInstance()->cannotMove()) {
            if (Options::getInstance()->shake) {
                this->messageDisplay(GameMessageNoMovesShake);
            } else {
                this->messageDisplay(GameMessageNoMovesMenu);
            }
        }
    }
}

void GameScene::onCompletedLevel() {
    log("GameScene level complete!");
    this->messageDisplay(GameMessageNoMessage);
    
    auto colorLayer = LayerColor::create(Color4B(0, 0, 0, 60),
                                         Director::getInstance()->getVisibleSize().width,
                                         Director::getInstance()->getVisibleSize().height);
    colorLayer->setTag(GameTagLayerColor);
    this->addChild(colorLayer, GameSceneDrawingOrderColorLayer);
    
    auto gameWinLayerListener = EventListenerTouchOneByOne::create();
    gameWinLayerListener->onTouchBegan = [&](Touch* touch, Event* event){
        return true;
    };
    gameWinLayerListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(gameWinLayerListener, colorLayer);
    
    auto gameWinLayer = GameWinLayer::create();
    gameWinLayer->setPosition(_visibleSize.width / 2,
                               _visibleSize.height / 2);
    this->addChild(gameWinLayer, GameSceneDrawingOrderMenuLayer);
    
    int perfect = GameData::getInstance()->getStepNumber() - GameData::getInstance()->getMinStepNumber();
    std::string perfectString = "";
    if (perfect < 1) {
        perfectString = "Perfect !";
        perfect = 3;
    } else if (perfect < 3) {
        perfectString = "Good Job ! \n" + StringUtils::format("%d Moves Away From Perfect", perfect);
        perfect = 2;
    } else {
        perfectString = "Good Job ! \n" + StringUtils::format("%d Moves Away From Perfect", perfect);
        perfect = 1;
    }
    Levels::getInstance()->markAsPerfect(GameData::getInstance()->getLevel(), perfect);
    gameWinLayer->setStars(perfect);
    gameWinLayer->setString(perfectString);
//    
//    log("level= %d", GameData::getInstance()->getLevel());
//    log("end level= %d", GameData::getInstance()->getEndLevel());
    if ((GameData::getInstance()->getLevel() % 10) == 0) {
        this->scheduleOnce(schedule_selector(GameScene::showAdmobInterstitial), 0);
    }
    
    
    // display the level complete nodes
//    auto levelCompleteLayer = LayerColor::create(Color4B(0, 0, 0, 0));
//    levelCompleteLayer->runAction(FadeTo::create(1.0f, 196));
//    this->addChild(levelCompleteLayer, GameSceneDrawingOrderMessageLayer);
//    
//    auto tipBackground = Sprite::createWithSpriteFrameName("game_tip_background.png");
//    tipBackground->runAction(FadeIn::create(0.5f));
//    tipBackground->setPosition(_visibleSize.width / 2.0f,
//                               _visibleSize.height / 2.0f);
//    levelCompleteLayer->addChild(tipBackground);
    
    // figure out the level complete text
//    Label* levelCompleteLabel;
//    Label* levelCompleteLabel2;
//    Label* levelCompleteLabel3;
//    std::string completeText;
//    int moves = GameData::getInstance()->getMovesLeft();
//    switch (GameData::getInstance()->getDifficulty()) {
//        case GameDifficultyEasy:   moves -= 10; break;
//        case GameDifficultyMedium: moves -= 6; break;
//        case GameDifficultyHard:   moves -= 2; break;
//    }
//    moves *= -1;
//    if (moves <= 0) {
//        levelCompleteLabel = Label::createWithSystemFont("Perfect!", "arial.ttf", 35.0f);
//        levelCompleteLabel->runAction(FadeIn::create(0.5f));
//        levelCompleteLabel->setPosition(160, 160);
//        levelCompleteLayer->addChild(levelCompleteLabel);
        
//        auto levelCompletePerfect = Sprite::createWithSpriteFrameName("game_level_complete_perfect.png");
//        levelCompletePerfect->setPosition(160, 204);
//        levelCompletePerfect->runAction(FadeIn::create(0.5f));
//        levelCompleteLayer->addChild(levelCompletePerfect);
        
        // update level to be perfect
//        int perfect = moves + 3;
//        if (perfect < 0) {
//            perfect = 1;
//        }
//
//        
//        // check for perfectionist achievement
//        int perfectLevels = Levels::getInstance()->perfectLevels();
//        if (perfectLevels >= 10) {
//            this->unlockAchievement(AchievementPerfectionist);
//        }
//        // check for professional perfectionist achievement
//        if (perfectLevels >= 30) {
//            this->unlockAchievement(AchievementProfessionalPerfectionist);
//        }
//        // check for mastermind
//        if (perfectLevels >= TOTAL_LEVELS) {
//            this->unlockAchievement(AchievementMastermind);
//        }
//    } else {
//        levelCompleteLabel = Label::createWithSystemFont("Good Job!", "arial.ttf" , 30.0f);
//        levelCompleteLabel->runAction(FadeIn::create(0.5f));
//        levelCompleteLabel->setPosition(160, 210);
//        levelCompleteLayer->addChild(levelCompleteLabel);
//        
//        if (moves == 1)
//            completeText = "1 Move Away";
//            else
//                completeText = StringUtils::format("%d Moves Away", moves);
//        
//        levelCompleteLabel2 = Label::createWithSystemFont(completeText, "arial.ttf", 30.0f);
//        levelCompleteLabel2->runAction(FadeIn::create(0.5f));
//        levelCompleteLabel2->setPosition(160, 177);
//        levelCompleteLayer->addChild(levelCompleteLabel2);
//        
//        levelCompleteLabel3 = Label::createWithSystemFont("From Perfect", "arial.ttf", 30.0f);
//        levelCompleteLabel3->runAction(FadeIn::create(0.5f));
//        levelCompleteLabel3->setPosition(160, 144);
//        levelCompleteLayer->addChild(levelCompleteLabel3);
//    }
    
    GameData::getInstance()->beatLevel();
    
    // delete the saved game - if they continue, then load the next one
    GameData::getInstance()->deleteSavedGame();
    
//    // check for "Begin the Hunt" achievement
//    bool beginTheHunt = true;
//    for (int i=0; i<10; i++) {
//        Level* l = (Level*) Levels::getInstance()->getLevels().at(i);
//        if (l->getComplete() == false) {
//            beginTheHunt = false;
//            break;
//        }
//    }
//    
//    if (beginTheHunt) this->unlockAchievement(AchievementBeginTheHunt);
//    
//    // check for "Enter the Darkness" achievement
//    bool enterTheDarkness = true;
//    for(int i=0; i<30; i++) {
//        Level* l = (Level*) Levels::getInstance()->getLevels().at(i);
//        if (l->getComplete() == false) {
//            enterTheDarkness = false;
//            break;
//        }
//    }
//    if (enterTheDarkness) this->unlockAchievement(AchievementEnterTheDarkness);
//    
//    // check for "Enjoy the Sun" achievement
//    bool enjoyTheSun = true;
//    for(int i=30; i<60; i++) {
//        Level* l = (Level*) Levels::getInstance()->getLevels().at(i);
//        if(l->getComplete() == false) {
//            enjoyTheSun = false;
//            break;
//        }
//    }
//    if(enjoyTheSun) this->unlockAchievement(AchievementEnjoyTheSun);
//    
//    // check for "Arrrgh!" achievement
//    bool arrrgh = true;
//    for(int i=60; i<90; i++) {
//        Level* l = (Level*) Levels::getInstance()->getLevels().at(i);
//        if(l->getComplete() == false) {
//            arrrgh = false;
//            break;
//        }
//    }
//    if(arrrgh) this->unlockAchievement(AchievementArrrgh);
//    
//    // check for difficulty achievements
//    bool treasureHunter = true;
//    bool anAdventurerIsYou = true;
//    bool intrepidExplorer = true;
//    // check for "Treasure Hunter" achievement
//    for(int i=0; i<120; i++) {
//        Level* l =  (Level*) Levels::getInstance()->getLevels().at(i);
//        if(l->getCompleteEasy() == false) treasureHunter = false;
//            if(l->getCompleteMedium() == false) anAdventurerIsYou = false;
//                if(l->getCompleteHard() == false) intrepidExplorer = false;
//                    if(!treasureHunter && !anAdventurerIsYou && !intrepidExplorer) break;
//    }
//    if(treasureHunter)    this->unlockAchievement(AchievementTreasureHunter);
//    if(anAdventurerIsYou) this->unlockAchievement(AchievementAnAdventurerIsYou);
//    if(intrepidExplorer)  this->unlockAchievement(AchievementIntrepidExplorer);
}

#pragma mark - for touch callback function

void GameScene::messageDisplay(int messageToDisplay) {
    _message = messageToDisplay;
    auto spriteMessage = (Sprite*) this->getChildByTag(GameTagMessage);
    if (spriteMessage != nullptr) {
        this->removeChildByTag(GameTagMessage);
        spriteMessage = nullptr;
    }
    
    // which message?
    switch(messageToDisplay) {
        case GameMessageNoMessage:
            log("GameScene getting rid of message");
            break;
        case GameMessageSwipeScreen:
            log("GameScene display message intro");
            spriteMessage = Sprite::createWithSpriteFrameName("game_message_intro.png");
            spriteMessage->setPosition(_visibleSize.width / 2.0f,
                                       _visibleSize.height / 2.0f);
            break;
        case GameMessageNoMovesMenu:
//            log("GameScene display message no moves menu");
//            spriteMessage = Sprite::createWithSpriteFrameName("game_message_no_moves_menu.png");
//            spriteMessage->setPosition(_visibleSize.width / 2.0f,
//                                       _visibleSize.height / 2.0f);
//            break;
        case GameMessageNoMovesShake:
            log("GameScene display message no moves shake");
            auto layer = GameWarningLayer::create();
            layer->setString("No Moves Available Tap to Restart");
            layer->setPosition(_visibleSize.width / 2.0f,
                               _visibleSize.height / 2.0f);
            this->addChild(layer, GameSceneDrawingOrderMenuLayer);
//            spriteMessage = Sprite::createWithSpriteFrameName("game_message_no_moves_shake.png");
//            spriteMessage->setPosition(_visibleSize.width / 2.0f,
//                                       _visibleSize.height / 2.0f);
            break;
    }
    
//    if (spriteMessage != nullptr) {
//        spriteMessage->setOpacity(0);
//        spriteMessage->runAction(Sequence::create(FadeIn::create(1.0f),
//                                                  DelayTime::create(3.0f),
//                                                  FadeOut::create(1.0f),
//                                                  CallFunc::create(CC_CALLBACK_0(GameScene::onRemoveMessage, this)),
//                                                  NULL));
//        this->addChild(spriteMessage, GameSceneDrawingOrderMessageLayer, GameTagMessage);
//    }
}

void GameScene::onRemoveMessage() {
    this->removeChildByTag(GameTagMessage);
}

#pragma mark - for touch callback function

void GameScene::unlockAchievement(int achievementId) {
    // unlock it
    if (Achievements::getInstance()->unlock(achievementId)) {
        Sound::getInstance()->playUnlockAchievement();
        
        // create achievement layer
        auto achievementLayer = Layer::create();
        this->addChild(achievementLayer, 5, GameTagAchievementLayer);
        
        // add background and labels to it
        auto achievementBackground = Sprite::createWithSpriteFrameName("game_achievement_background.png");
        achievementBackground->setPosition(160, 108);
        achievementLayer->addChild(achievementBackground, 0);
        
        auto achievementTitle =  Label::createWithSystemFont(Achievements::getInstance()->getName(achievementId), "arial.ttf", 26.0f);
        achievementTitle->setColor(Color3B(255, 255, 255));
        achievementTitle->setPosition(211, 61);
        achievementLayer->addChild(achievementTitle, 1);
        
        auto achievementDesc = Label::createWithSystemFont(Achievements::getInstance()->getDescription(achievementId), "arial.ttf", 20.0f);
        achievementDesc->setColor(Color3B(196, 207, 226));
        achievementDesc->setPosition(211, 37);
        achievementLayer->addChild(achievementDesc, 1);
        
        // animate it
        achievementLayer->setPosition(0, -220);
        achievementLayer->runAction(Sequence::create(MoveTo::create(1.0f, Vec2(0, 0)),
                                                     DelayTime::create(2.0f),
                                                     MoveTo::create(1.0f, Vec2(0, -220)),
                                                     CallFunc::create(CC_CALLBACK_0(GameScene::onRemoveAchievement, this)),
                                                     NULL));
    }
}

void GameScene::onRemoveAchievement() {
    this->removeChildByTag(GameTagAchievementLayer);
}


void GameScene::shake() {
    if (Options::getInstance()->shake && _firstMove) {
        log("GameScene shake detected, restarting level");
        Sound::getInstance()->playRestartLevel();
        GameData::getInstance()->loadLevel();
        this->restartLevel();
    }
}


#pragma mark - for touch callback function

bool GameScene::onTouchBegan(Touch * touch, Event *event) {
    _touchStart = this->convertTouchToNodeSpace(touch);
    return true;
}

void GameScene::onTouchEnded(Touch * touch, Event *event) {
    auto touchEnd = this->convertTouchToNodeSpace(touch);
    
    // remove swipe message, if it's there
    if (_message == GameMessageSwipeScreen) this->messageDisplay(GameMessageNoMessage);
    
    // if the game has been won, ignore other touches and load next level
    if (_won) {
        // if this is the last level, return to main menu
        if (GameData::getInstance()->getLevel() == TOTAL_LEVELS) {
            Sound::getInstance()->playClick();
            Sound::getInstance()->startMusicMenu();
            this->unsetCurrentGame();
            Director::getInstance()->replaceScene(TransitionFade::create(0.3f, MenuScene::createScene()));
        } else {
            // play click, change music
            Sound::getInstance()->playClick();
            Sound::getInstance()->startMusicGameplay();
            
            // load the next level
            int stage = GameData::getInstance()->stageForLevel(GameData::getInstance()->getLevel());
            int nextLevelStage = GameData::getInstance()->stageForLevel(GameData::getInstance()->getLevel() + 1);
            if (stage != nextLevelStage) {
                // if the next stage is locked, go to select level scene instead
                if (GameData::getInstance()->stageLocked(nextLevelStage)) {
                    this->unsetCurrentGame();
                    Director::getInstance()->replaceScene(TransitionFade::create(0.3f, SelectLevelScene::createScene()));
                    return;
                } else {
                    // otherwise go to the map scene
                    this->unsetCurrentGame();
                    Director::getInstance()->replaceScene(TransitionFade::create(0.3f, MapScene::sceneWithStage(nextLevelStage)));
                }
            } else {
                GameData::getInstance()->setLevel(GameData::getInstance()->getLevel() + 1);
                GameData::getInstance()->loadLevel();
                this->restartLevel();
            }
        }
        return;
    }
    
    // handle other touches
    int direction = Helpers::swipeDirection(_touchStart, touchEnd);
    switch (direction) {
        case GameDirUp: log("GameScene swiped up"); break;
        case GameDirDown: log("GameScene swiped down"); break;
        case GameDirLeft: log("GameScene swiped left"); break;
        case GameDirRight: log("GameScene swiped right"); break;
    }
    if(direction == GameDirLeft || direction == GameDirRight || direction == GameDirDown) {
        this->moveKeys(direction);
    }
}

void GameScene::onMenu(Ref* sender) {
    if(_won) return;
    log("GameScene onMenu");
    Sound::getInstance()->playClick();
    this->unsetCurrentGame();

    auto menuLayer = GameMenuLayer::create();
    menuLayer->setPosition(_visibleSize.width / 2.0f,
                           _visibleSize.height / 2.0f);
    this->addChild(menuLayer, GameSceneDrawingOrderMenuLayer);
    
    auto colorLayer = LayerColor::create(Color4B(0, 0, 0, 60),
                                         Director::getInstance()->getVisibleSize().width,
                                         Director::getInstance()->getVisibleSize().height);
    colorLayer->setTag(GameTagLayerColor);
    this->addChild(colorLayer, GameSceneDrawingOrderColorLayer);
    
    auto menuLayerListener = EventListenerTouchOneByOne::create();
    menuLayerListener->onTouchBegan = [&](Touch* touch, Event* event){
        return true;
    };
    menuLayerListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(menuLayerListener, colorLayer);
    
//    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.3f, GameMenuScene::createScene(), false));
}

void GameScene::onBack(Ref* sender) {
    log("GameScene onBack");
    Sound::getInstance()->playClick();

    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.3f, SelectLevelScene::createScene(), false));
}

void GameScene::removeMenuLayer() {
    if (this->getChildByTag(GameTagLayerColor)) {
        this->removeChildByTag(GameTagLayerColor);
    }
}

void GameScene::addIntroLayer() {
    auto introLayer = GameIntroLayer::create();
    this->addChild(introLayer, GameSceneDrawingOrderIntroLayer);
}


void GameScene::showAdmobInterstitial(float dt) {
    SonarCocosHelper::AdMob::showFullscreenAd();
}


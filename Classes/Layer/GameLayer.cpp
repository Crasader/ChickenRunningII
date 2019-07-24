//
//  LevelListLayer.cpp
//  HuaRong
//
//  Created by kangbiao on 15/5/27.
//
//

#include "GameLayer.h"
#include "GameData.h"
#include "GameTile.h"

GameLayer::GameLayer()
{}

GameLayer::~GameLayer() {
}

bool  GameLayer::init() {
    if ( ! Layer::init() )
    {
        return false;
    }
  
    this->initBackground();
    this->initTiles();
    
    return true;
}

#pragma mark - for init function

void GameLayer::initBackground() {
    // background
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto background = Sprite::create("images/scene_background.png");
    background->setPosition(visibleSize.width / 2,
                            visibleSize.height / 2);
    this->addChild(background, GameLayerDrawingOrderBackground);
}

void GameLayer::initTiles() {
    // draw the tiles
    int x,y;
    GameTile* tile;
    for (x = 0; x < GAME_BOARD_WIDTH; x++) {
        for (y = 0; y < GAME_BOARD_HEIGHT; y++) {
            int tileType = GameData::getInstance()->getTileType(x, y);
            if (tileType != GameTileSpace) {
                tile = GameTile::create(tileType, x, y);
                this->addChild(tile, GameLayerDrawingOrderTiles, GameTagTiles+(GAME_BOARD_WIDTH * y + x));
            }
        }
    }
    
    // draw the keys
    for(int i = 0; i < GameData::getInstance()->getKeys().size(); i++) {
        GameDataKey* key = GameData::getInstance()->getKeys().at(i);
        if (! key->getUsed()) {
            tile = GameTile::create(GameTileKey, key->getX(), key->getY());
            this->addChild(tile, GameLayerDrawingOrderTiles, GameTagKeys + i);
        }
    }
    
    // check for winning
    _won = false;
    
    // message
    //    if (GameData::getInstance()->getLevel() == 1) {
    //        this->messageDisplay(GameMessageSwipeScreen);
    //    }
    
    // only save the game if a move has been made
    _firstMove = false;
    
    // achievements
//    _isAchievementActive = false;
    
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->setSwallowTouches(true);
//    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
//    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}

#pragma mark - for touch callback function

//bool GameLayer::onTouchBegan(Touch * touch, Event *event) {
//    _touchStart = this->convertTouchToNodeSpace(touch);
//    return true;
//}
//
//void GameLayer::onTouchEnded(Touch * touch, Event *event) {
//    auto touchEnd = this->convertTouchToNodeSpace(touch);
//    
//    // remove swipe message, if it's there
//    if (_message == GameMessageSwipeScreen) this->messageDisplay(GameMessageNoMessage);
//    
//    // if the game has been won, ignore other touches and load next level
//    if (_won) {
//        // if this is the last level, return to main menu
//        if (GameData::getInstance()->getLevel() == TOTAL_LEVELS) {
//            Sound::getInstance()->playClick();
//            Sound::getInstance()->startMusicMenu();
//            this->unsetCurrentGame();
//            Director::getInstance()->replaceScene(TransitionFade::create(0.3f, MenuScene::createScene()));
//        } else {
//            // play click, change music
//            Sound::getInstance()->playClick();
//            Sound::getInstance()->startMusicGameplay();
//            
//            // load the next level
//            int stage = GameData::getInstance()->stageForLevel(GameData::getInstance()->getLevel());
//            int nextLevelStage = GameData::getInstance()->stageForLevel(GameData::getInstance()->getLevel() + 1);
//            if (stage != nextLevelStage) {
//                // if the next stage is locked, go to select level scene instead
//                if (GameData::getInstance()->stageLocked(nextLevelStage)) {
//                    this->unsetCurrentGame();
//                    Director::getInstance()->replaceScene(TransitionFade::create(0.3f, SelectLevelScene::createScene()));
//                    return;
//                } else {
//                    // otherwise go to the map scene
//                    this->unsetCurrentGame();
//                    Director::getInstance()->replaceScene(TransitionFade::create(0.3f, MapScene::sceneWithStage(nextLevelStage)));
//                }
//            } else {
//                GameData::getInstance()->setLevel(GameData::getInstance()->getLevel() + 1);
//                GameData::getInstance()->loadLevel();
//                this->restartLevel();
//            }
//        }
//        return;
//    }
//    
//    // handle other touches
//    int direction = Helpers::swipeDirection(_touchStart, touchEnd);
//    switch (direction) {
//        case GameDirUp: log("GameScene swiped up"); break;
//        case GameDirDown: log("GameScene swiped down"); break;
//        case GameDirLeft: log("GameScene swiped left"); break;
//        case GameDirRight: log("GameScene swiped right"); break;
//    }
//    if(direction == GameDirLeft || direction == GameDirRight || direction == GameDirDown) {
//        this->moveKeys(direction);
//    }
//}

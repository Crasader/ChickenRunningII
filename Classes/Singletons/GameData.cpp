#include "GameData.h"
#include "Helpers.h"

using namespace std;

GameData* GameData::_instance = nullptr;

GameData* GameData::getInstance() {
    if (_instance == nullptr) {
        _instance = new GameData();
        _instance->init();
    }
    
    return _instance;
}

void GameData::init()
{
    log("GameData init");
    _stepNumber   = 0;
    _minStepNumber = 0;
    _isActiveGame = false;
    _options = Options::getInstance();
//    _levels  = Levels::getInstance();
    _sound   = Sound::getInstance();
    
    _keys.clear();
//    this->loadLevel();
}

// getters, because obj-c is weird
int GameData::getTileType(int x, int y) {
    return _tiles[x][y];
}

void GameData::printTile() {
    for (int x = 0; x< GAME_BOARD_WIDTH; x++) {
        for (int y = 0; y < GAME_BOARD_HEIGHT; y++) {
            log("x=%d, y=%d, tile=%d", x, y, _tiles[x][y]);
        }
    }
}

std::string GameData::getTileString() {
    return _tileString;
}

// saving, loading
std::string GameData::savedGamePath() {
    auto filePath = FileUtils::getInstance()->getWritablePath();
    return filePath + "SavedGame.plist";
}

void GameData::loadLevel() {
    auto level = Levels::getInstance()->getLevels().at(_level - 1);
    
    // tiles
    log("level data: %s", level->getData().c_str());
    strcpy(_tileString, level->getData().c_str());
    
    // moves
    _movesLeft = level->getMinMoves();
    _stepNumber = 0;
    _minStepNumber = level->getMinMoves();
    
    // make sure the stage is correct
    _stage = this->stageForLevel(_level);
    
    // set difficulty
    _difficulty = _options->difficulty;
    
    // update moves left based on difficulty
    switch(_difficulty) {
        case GameDifficultyEasy:   _movesLeft += 10; break;
        case GameDifficultyMedium: _movesLeft += 6; break;
        case GameDifficultyHard:   _movesLeft += 2; break;
    }
    
    // set up tiles
    this->freeKeys();
    int keyId = 0;
    int x, y;
    for (x = 0; x< GAME_BOARD_WIDTH; x++) {
        for (y = 0; y < GAME_BOARD_HEIGHT; y++) {
            char c = _tileString[GAME_BOARD_WIDTH * y + x];
            switch(c) {
                case '.': // space
                default:
                    _tiles[x][y] = GameTileSpace;
                    break;
                case '*': // solid
                    _tiles[x][y] = GameTileSolid4Sides;
                    break;
                case '!': // key
                {
                    _tiles[x][y] = GameTileSpace;
                    GameDataKey* key = GameDataKey::create(x, y, false, keyId);
                    keyId++;
                    _keys.pushBack(key);
                }
                    break;
                case 'x': // chest
                    _tiles[x][y] = GameTileChest;
                    break;
                case 'X': // open chest
                    _tiles[x][y] = GameTileChestOpen;
                    break;
                case 'o': // door switch
                    _tiles[x][y] = GameTileSwitch;
                    break;
                case '|': // left-right door closed
                    _tiles[x][y] = GameTileDoorLRClosed;
                    break;
                case '#': // left-right door open
                    _tiles[x][y] = GameTileDoorLROpen;
                    break;
                case '-': // top-bottom door closed
                    _tiles[x][y] = GameTileDoorTBClosed;
                    break;
                case '=': // top-bottom door open
                    _tiles[x][y] = GameTileDoorTBOpen;
                    break;
            }
        }
    }
    // figure out what all the walls should look like
    bool top, right, bottom, left;
    for(x=0; x<GAME_BOARD_WIDTH; x++) {
        for(y=0; y<GAME_BOARD_HEIGHT; y++) {
            if(_tiles[x][y] == GameTileSolid4Sides) {
                top = false; right = false; bottom = false; left = false;
                if(y == 0 || (_tiles[x][y-1] >= GameTileSolid4Sides && _tiles[x][y-1] <= GameTileSolid0Sides))
                    top = true;
                    if(x == GAME_BOARD_WIDTH-1 || (_tiles[x+1][y] >= GameTileSolid4Sides && _tiles[x+1][y] <= GameTileSolid0Sides))
                        right = true;
                        if(y == GAME_BOARD_HEIGHT-1 || (_tiles[x][y+1] >= GameTileSolid4Sides && _tiles[x][y+1] <= GameTileSolid0Sides))
                            bottom = true;
                            if(x == 0 || (_tiles[x-1][y] >= GameTileSolid4Sides && _tiles[x-1][y] <= GameTileSolid0Sides))
                                left = true;
                                
                                // set the walls tiles
                                if(top && right && bottom && left)
                                    _tiles[x][y] = GameTileSolid4Sides;
                                    else if(top && right && bottom && !left)
                                        _tiles[x][y] = GameTileSolid3SidesTRB;
                                        else if(top && right && !bottom && left)
                                            _tiles[x][y] = GameTileSolid3SidesTRL;
                                            else if(top && !right && bottom && left)
                                                _tiles[x][y] = GameTileSolid3SidesTLB;
                                                else if(!top && right && bottom && left)
                                                    _tiles[x][y] = GameTileSolid3SidesRBL;
                                                    else if(top && right && !bottom && !left)
                                                        _tiles[x][y] = GameTileSolid2SidesTR;
                                                        else if(top && !right && bottom && !left)
                                                            _tiles[x][y] = GameTileSolid2SidesTB;
                                                            else if(top && !right && !bottom && left)
                                                                _tiles[x][y] = GameTileSolid2SidesTL;
                                                                else if(!top && right && bottom && !left)
                                                                    _tiles[x][y] = GameTileSolid2SidesRB;
                                                                    else if(!top && right && !bottom && left)
                                                                        _tiles[x][y] = GameTileSolid2SidesRL;
                                                                        else if(!top && !right && bottom && left)
                                                                            _tiles[x][y] = GameTileSolid2SidesBL;
                                                                            else if(top && !right && !bottom && !left)
                                                                                _tiles[x][y] = GameTileSolid1SidesT;
                                                                                else if(!top && right && !bottom && !left)
                                                                                    _tiles[x][y] = GameTileSolid1SidesR;
                                                                                    else if(!top && !right && bottom && !left)
                                                                                        _tiles[x][y] = GameTileSolid1SidesB;
                                                                                        else if(!top && !right && !bottom && left)
                                                                                            _tiles[x][y] = GameTileSolid1SidesL;
                                                                                            else if(!top && !right && !bottom && !left)
                                                                                                _tiles[x][y] = GameTileSolid0Sides;
                                                                                                }
        }
    }
//    this->printTile();
}

bool GameData::loadGame() {
    if(! this->isSavedGame())
        return false;

    ValueVector savedGame = FileUtils::getInstance()->getValueVectorFromFile(this->savedGamePath());
    
    // load saved game
    _stage = savedGame.at(0).asInt();
    _difficulty = savedGame.at(1).asInt();
    _options->difficulty = _difficulty;
    _level     = savedGame.at(2).asInt();
    _movesLeft = savedGame.at(4).asInt();
    _stepNumber = savedGame.at(6).asInt();
    
    // tile string
    strcpy(_tileString, savedGame.at(3).asString().c_str());
    
    // keys are special (key string format is "x,y,used:x,y,used:x,y,used")
    _keys.clear();
    std::string keyString = savedGame.at(5).asString();
    std::vector<std::string> keyPairs = Helpers::explodeString(":", keyString);
    int keyId = 0;
    for (int i = 0; i < keyPairs.size(); i++) {
        std::vector<std::string> keyPair = Helpers::explodeString(",", keyPairs.at(i));
        auto key = GameDataKey::create(atoi(keyPair.at(0).c_str()),
                                       atoi(keyPair.at(1).c_str()),
                                       Helpers::to_bool(keyPair.at(2)),
                                       keyId);

        keyId++;
        
        _keys.pushBack(key);
    }
    
    // set up the tiles
    int x, y;
    for(x=0; x<GAME_BOARD_WIDTH; x++)
        for(y=0; y<GAME_BOARD_HEIGHT; y++)
            _tiles[x][y] = _tileString[GAME_BOARD_WIDTH*y+x]-'A';
            
            return true;
}

void GameData::saveGame() {
    // set up tile string
    int x, y;
    for(x=0; x<GAME_BOARD_WIDTH; x++)
        for(y=0; y<GAME_BOARD_HEIGHT; y++)
            _tileString[GAME_BOARD_WIDTH*y+x] = _tiles[x][y]+'A';
            _tileString[GAME_BOARD_WIDTH*GAME_BOARD_HEIGHT] = '\0';
            
            // make the key string
            std::string keyString = "";
            for (int i = 0; i < _keys.size(); i++) {
                GameDataKey* key = _keys.at(i);
                std::string chunk = StringUtils::format("%d,%d,%d", key->getX(), key->getY(), key->getUsed());
                keyString.append(chunk);
                if (i < _keys.size() - 1) {
                    keyString.append(":");
                }
            }
    
    // save the game
    ValueVector savedGame;
    savedGame.push_back(Value(StringUtils::format("%d", _stage)));
    savedGame.push_back(Value(StringUtils::format("%d", _difficulty)));
    savedGame.push_back(Value(StringUtils::format("%d", _level)));
    savedGame.push_back(Value(StringUtils::format("%s", _tileString)));
    savedGame.push_back(Value(StringUtils::format("%d", _movesLeft)));
    savedGame.push_back(Value(StringUtils::format("%s", keyString.c_str())));
    savedGame.push_back(Value(StringUtils::format("%d", _stepNumber)));
    
    if (FileUtils::getInstance()->writeValueVectorToFile(savedGame, this->savedGamePath())) {
        log("GameData wrote file");
    } else log("GameData file not written");
}

bool GameData::isSavedGame() {
    return FileUtils::getInstance()->isFileExist(this->savedGamePath());
}

void GameData::deleteSavedGame() {
    FileUtils::getInstance()->removeFile(this->savedGamePath());
}

// gameplay mechanics
void GameData::moveKeys(int dir) {
    int x, y, newX=-1, newY=-1;
    int keysMoved = 0;
    std::vector<std::string> doorsSwitched;
    unsigned int i,j;
    GameDataKey* key;
    GameDataKey* key2;
    bool hitChest = false; // debug
    
    // loop through the keys
    for (i = 0; i < _keys.size(); i++) {
        key = _keys.at(i);
        if (key->getUsed() == false) {
            // find the coordinates if the key moved
            switch(dir) {
                case GameDirLeft:
                    newX = key->getX() - 1;
                    newY = key->getY();
                    break;
                case GameDirRight:
                    newX = key->getX() + 1;
                    newY = key->getY();
                    break;
                case GameDirDown:
                    newX = key->getX();
                    newY = key->getY() + 1;
                    break;
            }
            
            // if it won't move off the board
            if(newX >= 0 && newX < GAME_BOARD_WIDTH && newY >= 0 && newY < GAME_BOARD_HEIGHT) {
                // if it hits nothing (or an open door), move it
                if(_tiles[newX][newY] == GameTileSpace || _tiles[newX][newY] == GameTileDoorLROpen || _tiles[newX][newY] == GameTileDoorTBOpen) {
                    key->setX(newX);
                    key->setY(newY);
                    keysMoved++;
                }
                
                // if it hits a chest, change it
                else if(_tiles[newX][newY] == GameTileChest) {
                    hitChest = true; //debug
                    key->setUsed(true);
                    _tiles[newX][newY] = GameTileChestOpen;
                    key->setX(newX);
                    key->setY(newY);
                    keysMoved++;
                    log("GameData a key hit a chest!");
                    
                    // play open chest sound
                    _sound->playOpenChest();
                }
                
                // if it hits a door switch, open doors
                else if(_tiles[newX][newY] == GameTileSwitch) {
                    // move key
                    key->setX(newX);
                    key->setY(newY);
                    keysMoved++;
                    // toggle doors
                    doorsSwitched.push_back(StringUtils::format("%d,%d", newX, newY));
                    log("GameData a key hit a switch");
                }
            }
        }
    }
    
    // now that the keys have moved, go back and undo any key stacking
    bool keysAreStacked = true;
    while(keysAreStacked) {
        keysAreStacked = false;
        // loop through keys
        for (i = 0; i < _keys.size(); i++) {
            key = _keys.at(i);
            
            // if these keys aren't used yet
            if (key->getUsed() == false) {
                // loop through keys again
                for (j = 0 ; j < _keys.size(); j++) {
                    key2 = _keys.at(j);
                    
                    // and if these ones aren't used
                    if (key2->getUsed() == false) {
                        // and we're not looking at the same key
                        if(key->getIdent() != key2->getIdent()) {
                            // and if they have the same coordinates
                            if(key->getX() == key2->getX() && key->getY() == key2->getY()) {
                                log("GameData keys are stacked, unstacking...");
                                keysAreStacked = true;
                                switch(dir) {
                                    case GameDirLeft:
                                        newX = key->getX() + 1;
                                        newY = key->getY();
                                        keysMoved--;
                                        break;
                                    case GameDirRight:
                                        newX = key->getX() - 1;
                                        newY = key->getY();
                                        keysMoved--;
                                        break;
                                    case GameDirDown:
                                        newX = key->getX();
                                        newY = key->getY() - 1;
                                        keysMoved--;
                                        break;
                                }
                                // if we unstack the key that hit the door, we didn't actually hit the door
                                if (doorsSwitched.size() > 0) {
                                    std::string doorSwitchedString = StringUtils::format("%d,%d", key->getX(), key->getY());
                                    for (int index = 0; index < doorsSwitched.size(); index++) {
                                        if (doorsSwitched.at(index).compare(doorSwitchedString) == 0) {
                                            log("GameData nevermind, the key that hit the door switch moved back");
                                            doorsSwitched.erase(doorsSwitched.begin() + index);
                                            break;
                                        }
                                    }
                                }
                                key->setX(newX);
                                key->setY(newY);
                            }
                        }
                    }
                }
            }
        }
    }
    
    // if doors have changed, lets make sure we haven't closed any doors on keys
    if (doorsSwitched.size() > 0) {
        _doorOpened = true;
        // play door sound
        _sound->playDoor();
        
        // open/close doors
        for (x=0; x<GAME_BOARD_WIDTH; x++) {
            for (y=0; y<GAME_BOARD_HEIGHT; y++) {
                // open closed doors
                if (_tiles[x][y] == GameTileDoorLRClosed) {
                    _tiles[x][y] = GameTileDoorLROpen;
                } else if(_tiles[x][y] == GameTileDoorTBClosed) {
                    _tiles[x][y] = GameTileDoorTBOpen;
                }
                // close open doors?
                else if(_tiles[x][y] == GameTileDoorLROpen || _tiles[x][y] == GameTileDoorTBOpen) {
                    bool closeDoor = true;
                    for (i=0; i < _keys.size(); i++) {
                        key = _keys.at(i);
                        
                        if (key->getUsed() == false) {
                            // is there a key blocking this door?
                            if (key->getX() == x && key->getY() == y) {
                                closeDoor = false;
                                log("GameData can't close a door, there's a key in the way");
                            }
                        }
                    }
                    // if we're supposed to close, or we're supposed to not close a different door
                    if(closeDoor) {
                        // then close
                        if (_tiles[x][y] == GameTileDoorLROpen) {
                            _tiles[x][y] = GameTileDoorLRClosed;
                        } else {
                            _tiles[x][y] = GameTileDoorTBClosed;
                        }
                    } else {
                        log("close door should be FALSE, right?");
                    }
                }
            }
        }
    } else {
        _doorOpened = false;
    }
    
    // if keys have indeed moved, substract from movesLeft
    if (keysMoved > 0) {
        _movesLeft--;
        _stepNumber++;
        // play key move sounds
        _sound->playKeyMove();
    }
    
    if (hitChest) {
        hitChest = true; // debug
    }
}

bool GameData::cannotMove() {
    int tile;
    GameDataKey* key;
    
    // loop through keys seeing if they can move
    for (unsigned int i = 0; i < _keys.size(); i++) {
        key = _keys.at(i);
        
        if (key->getUsed() == false) {
            // left
            if(key->getX() > 0) {
                tile = _tiles[key->getX() - 1][key->getY()];
                if ((tile == GameTileSpace || tile == GameTileChest || tile == GameTileDoorLROpen || tile == GameTileDoorTBOpen || tile == GameTileSwitch)
                    && !this->isKeyAtPosition(key->getX() - 1, key->getY())) {
                    return false;
                }
            }
            
            // right
            if(key->getX() < GAME_BOARD_WIDTH-1) {
                tile = _tiles[key->getX()+1][key->getY()];
                if((tile == GameTileSpace || tile == GameTileChest || tile == GameTileDoorLROpen || tile == GameTileDoorTBOpen || tile == GameTileSwitch)
                   && !this->isKeyAtPosition(key->getX() +1, key->getY())) {
                    return false;
                }
            }
            
            // down
            if(key->getY() < GAME_BOARD_HEIGHT-1) {
                tile = _tiles[key->getX()][key->getY() + 1];
                if((tile == GameTileSpace || tile == GameTileChest || tile == GameTileDoorLROpen || tile == GameTileDoorTBOpen || tile == GameTileSwitch)
                   && !this->isKeyAtPosition(key->getX(), key->getY() + 1)) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool GameData::isKeyAtPosition(int x,int y) {
    GameDataKey* key;
    for(unsigned int i=0; i< _keys.size(); i++) {
        key = _keys.at(i);
        if (key->getX() == x && key->getY() == y) return true;
    }
    return false;
}

void GameData::beatLevel() {
    Level* l = Levels::getInstance()->getLevels().at(_level-1);
    l->setComplete(true);
    switch (_difficulty) {
        case GameDifficultyEasy:   l->setCompleteEasy(true);   break;
        case GameDifficultyMedium: l->setCompleteMedium(true); break;
        case GameDifficultyHard:   l->setCompleteHard(true);   break;
    }
    Levels::getInstance()->save();
    log("GameData marked level as complete");
}

// misc
bool GameData::stageLocked(int stageToCheck) {
    // levels per stage
    int min, max;
    switch (stageToCheck) {
        default:
        case GameStage2: // caves
            min = 1; max = 30;
            break;
        case GameStage3: // beach
            min = 31; max = 60;
            break;
        case GameStage4: // pirate ship
            min = 61; max = 90;
            break;
    }
    
    // search the levels
    bool locked = false;
    for(int i=min; i<=max; i++) {
        if(! Levels::getInstance()->isComplete(i)) {
            locked = true;
            break;
        }
    }
    return locked;
}

void GameData::setStageNumber(int stageNumber) {
    _stage = stageNumber;
    // levels per stage
    switch (stageNumber) {
        default:
        case GameStage1: // caves
            _startLevel = 1;
            _endLevel   = 30;
            break;
        case GameStage2: // beach
            _startLevel = 31;
            _endLevel   = 60;
            break;
        case GameStage3: // pirate ship
            _startLevel = 61;
            _endLevel   = 90;
            break;
        case GameStage4: // pirate ship
            _startLevel = 91;
            _endLevel   = 120;
            break;
    }
}

int GameData::stageForLevel(int levelToCheck) {
    if (levelToCheck <= 30)
        return GameStage1;
    else if(levelToCheck >= 31 && levelToCheck <= 60)
        return GameStage2;
    else if(levelToCheck >= 61 && levelToCheck <= 90)
        return GameStage3;
    else
        return GameStage4;
}

std::string GameData::stageName() {
    if (_stage == GameStage1) return "FOREST";
    else if(_stage == GameStage2) return "CAVES";
    else if(_stage == GameStage3) return "BEACH";
    else return "SHIP";
}

// memory
void GameData::freeKeys() {
    _keys.clear();
}

Vector<GameDataKey *> GameData::getKeys() {
    return _keys;
}


#ifndef __GameData_H__
#define __GameData_H__

#include "cocos2d.h"
#include "Levels.h"
#include "Options.h"
#include "Sound.h"
#include "GameDataKey.h"

USING_NS_CC;

// game board dimensions
#define GAME_BOARD_WIDTH 6
#define GAME_BOARD_HEIGHT 8

// levels
#define TOTAL_LEVELS 120

// stage names
typedef enum {
    GameStage1 = 0,
    GameStage2 = 1,
    GameStage3 = 2,
    GameStage4 = 3,
    GameStageNone = 4
} GameStageNames;

// difficulties
typedef enum {
    GameDifficultyEasy = 0,
    GameDifficultyMedium = 1,
    GameDifficultyHard = 2
} GameDifficulties;

// tile types
typedef enum {
    GameTileSpace = 0,
    GameTileSolid4Sides = 1,
    GameTileSolid3SidesTRB = 2,
    GameTileSolid3SidesTRL = 3,
    GameTileSolid3SidesTLB = 4,
    GameTileSolid3SidesRBL = 5,
    GameTileSolid2SidesTR = 6,
    GameTileSolid2SidesTB = 7,
    GameTileSolid2SidesTL = 8,
    GameTileSolid2SidesRB = 9,
    GameTileSolid2SidesRL = 10,
    GameTileSolid2SidesBL = 11,
    GameTileSolid1SidesT = 12,
    GameTileSolid1SidesR = 13,
    GameTileSolid1SidesB = 14,
    GameTileSolid1SidesL = 15,
    GameTileSolid0Sides = 16,
    GameTileKey = 17,
    GameTileChest = 18,
    GameTileChestOpen = 19,
    GameTileSwitch = 20,
    GameTileDoorLRClosed = 21,
    GameTileDoorLROpen = 22,
    GameTileDoorTBClosed = 23,
    GameTileDoorTBOpen = 24
} GameTiles;

class GameData
{
public:
    static GameData* getInstance();
    
    int getTileType(int x, int y);
    Vector<GameDataKey *> getKeys();
    
    void setStageNumber(int stageNumber);
private:
    static GameData * _instance;
    
    void init();
    
    Options* _options;
//    Levels* _levels;
    Sound* _sound;
    
    char _tiles[GAME_BOARD_WIDTH][GAME_BOARD_HEIGHT];

    // is the game active?
    CC_SYNTHESIZE(bool, _isActiveGame, ActiveGame);
    
    // shared data
    CC_SYNTHESIZE(int, _stage, Stage);
    CC_SYNTHESIZE(int, _level, Level);
    CC_SYNTHESIZE(int, _movesLeft, MovesLeft);
    CC_SYNTHESIZE(int, _stepNumber, StepNumber);
    CC_SYNTHESIZE(int, _minStepNumber, MinStepNumber);
    CC_SYNTHESIZE(int, _difficulty, Difficulty);
    CC_SYNTHESIZE(int, _startLevel, StartLevel);
    CC_SYNTHESIZE(int, _endLevel, EndLevel);
    CC_SYNTHESIZE(bool, _returnToGame, ReturnToGame);
    CC_SYNTHESIZE(bool, _doorOpened, DoorOpened);

    char _tileString[49];
    Vector<GameDataKey *> _keys;

// getters, because obj-c is weird
    std::string getTileString();

    // saving, loading
    std::string savedGamePath();
    void loadLevel();
    bool loadGame();
    void saveGame();
    bool isSavedGame();
    void deleteSavedGame();

// gameplay mechanics
    void moveKeys(int dir);
    bool cannotMove();
    bool isKeyAtPosition(int x, int y);
    void beatLevel();

// misc
    bool stageLocked(int stageToCheck);
    int stageForLevel(int levelToCheck);
    std::string stageName();

// memory
    void freeKeys();
    
    void printTile();
};

#endif // __GameData_H__

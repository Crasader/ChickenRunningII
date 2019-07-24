#include "GameTile.h"
#include "GameData.h"

GameTile::GameTile()
:_x(0)
,_y(0)
,_tileType(0)
,_tileWidth(0.0f)
,_leftMargin(0.0f)
,_bottomMargin(0.0f)
{}

GameTile* GameTile::create(int tileType, int x, int y) {
    GameTile* gameTile = new (std::nothrow) GameTile();
    if (gameTile && gameTile->init(tileType, x, y)) {
        gameTile->autorelease();
        return gameTile;
    } else  {
        delete gameTile;
        gameTile = NULL;
        return NULL;
    }
}

bool GameTile::init(int tileType, int x, int y) {
    if ( ! Sprite::init() ) {
        return false;
    }
    _x = x;
    _y = y;
    _tileType = tileType;
    
    auto sprite = Sprite::createWithSpriteFrameName("game_tile_key.png");
    _tileWidth = sprite->getContentSize().width;
 
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    _leftMargin = visibleSize.width / 2 - (GAME_BOARD_WIDTH / 2 * _tileWidth);
    _bottomMargin = 38.5f;
    this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->changePosition(x, y);
    this->changeType(tileType);
    this->setScale(1.0);
    
    return true;
}


void GameTile::changeType(int tileType) {
    _tileType = tileType;
    std::string imageName;
    switch(tileType) {
        case GameTileSolid4Sides:		imageName = "game_tile_solid_4.png"; break;
        case GameTileSolid3SidesTRB:	imageName = "game_tile_solid_3_trb.png"; break;
        case GameTileSolid3SidesTRL:	imageName = "game_tile_solid_3_trl.png"; break;
        case GameTileSolid3SidesTLB:	imageName = "game_tile_solid_3_tlb.png"; break;
        case GameTileSolid3SidesRBL:	imageName = "game_tile_solid_3_rbl.png"; break;
        case GameTileSolid2SidesTR:		imageName = "game_tile_solid_2_tr.png"; break;
        case GameTileSolid2SidesTB:		imageName = "game_tile_solid_2_tb.png"; break;
        case GameTileSolid2SidesTL:		imageName = "game_tile_solid_2_tl.png"; break;
        case GameTileSolid2SidesRB:		imageName = "game_tile_solid_2_rb.png"; break;
        case GameTileSolid2SidesRL:		imageName = "game_tile_solid_2_rl.png"; break;
        case GameTileSolid2SidesBL:		imageName = "game_tile_solid_2_bl.png"; break;
        case GameTileSolid1SidesT:		imageName = "game_tile_solid_1_t.png"; break;
        case GameTileSolid1SidesR:		imageName = "game_tile_solid_1_r.png"; break;
        case GameTileSolid1SidesB:		imageName = "game_tile_solid_1_b.png"; break;
        case GameTileSolid1SidesL:		imageName = "game_tile_solid_1_l.png"; break;
        case GameTileSolid0Sides:		imageName = "game_tile_solid_0.png"; break;
        case GameTileKey:				imageName = "game_tile_key.png"; break;
        case GameTileChest:				imageName = "game_tile_chest.png"; break;
        case GameTileChestOpen:			imageName = "game_tile_chestopen.png"; break;
        case GameTileSwitch:			imageName = "game_tile_switch.png"; break;
        case GameTileDoorLRClosed:		imageName = "game_tile_doorlrclose.png"; break;
        case GameTileDoorLROpen:		imageName = "game_tile_doorlropen.png"; break;
        case GameTileDoorTBClosed:		imageName = "game_tile_doortbclose.png"; break;
        case GameTileDoorTBOpen:		imageName = "game_tile_doortbopen.png"; break;
        default: imageName = "game_tile_key.png"; break;
    }
    this->setSpriteFrame(imageName);
}

void GameTile::changePosition(int x, int y) {
    _x = x;
    _y = y;
    
    this->setPosition(Vec2(x  * _tileWidth,
                            _tileWidth * ( GAME_BOARD_HEIGHT - 1 - y)));
}

#ifndef __GameTile_H__
#define __GameTile_H__

#include "cocos2d.h"

USING_NS_CC;

class GameTile : public Sprite
{
public:
    GameTile();
    
    static GameTile* create(int tileType, int x, int y);

private:
    virtual bool init(int tileType, int x, int y);
    
    CC_SYNTHESIZE(int, _tileType, TileType);
    CC_SYNTHESIZE(int, _x, X);
    CC_SYNTHESIZE(int, _y, Y);
    float _tileWidth;
    float _leftMargin, _bottomMargin;

    void changeType(int tileType);
    void changePosition(int x, int y);

};


#endif // __GameTile_H__

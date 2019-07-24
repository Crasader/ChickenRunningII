#include "GameDataKey.h"

GameDataKey::GameDataKey()
:_x(0)
,_y(0)
,_used(false)
,_ident(0)
{
    log("GameDataKey init");
}


GameDataKey* GameDataKey::create(int x, int y, bool used, int ident) {
    GameDataKey* key = new(std::nothrow) GameDataKey();
    if (key) {
        key->init(x, y, used, ident);
        key->autorelease();
        return key;
    } else  {
        delete key;
        key = NULL;
        return NULL;
    }
}

void GameDataKey::init(int x, int y, bool used, int ident) {
    _x = x;
    _y = y;
    _used = used;
    _ident = ident;
}
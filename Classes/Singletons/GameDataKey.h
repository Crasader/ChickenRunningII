#ifndef __GameDataKey_H__
#define __GameDataKey_H__

#include "cocos2d.h"

USING_NS_CC;

class GameDataKey : public Ref
{
public:
    GameDataKey();
    static GameDataKey* create(int x, int y, bool used, int ident);
private:
    CC_SYNTHESIZE(int, _x, X);
    CC_SYNTHESIZE(int, _y, Y);
    CC_SYNTHESIZE(bool, _used, Used);
    CC_SYNTHESIZE(int, _ident, Ident);
    
    void init(int x, int y, bool used, int ident);
};

#endif // __GameDataKey_H__

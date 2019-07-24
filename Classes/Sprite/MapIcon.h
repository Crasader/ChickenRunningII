#ifndef __GameTile_H__
#define __GameTile_H__

#include "cocos2d.h"

USING_NS_CC;

class MapIcon : public MenuItemSprite
{
public:
    MapIcon();
    
    static MapIcon* create(std::string labelString);
    
    void setLocked(int isLocked);
private:
    virtual bool init(std::string labelString);
    
    int _isLocked;
    Sprite* _icon;
    
};


#endif // __GameTile_H__

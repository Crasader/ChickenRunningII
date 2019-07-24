#include "MapIcon.h"
#include "GameData.h"

MapIcon::MapIcon()
:_isLocked(true)
{}

MapIcon* MapIcon::create(std::string labelString) {
    MapIcon* mapIcon = new (std::nothrow) MapIcon();
    if (mapIcon && mapIcon->init(labelString)) {
        mapIcon->autorelease();
        return mapIcon;
    } else  {
        delete mapIcon;
        mapIcon = NULL;
        return NULL;
    }
}

bool MapIcon::init(std::string labelString) {
    if (! MenuItemSprite::init() ) {
        return false;
    }
    auto baseNode = Node::create();
    
    auto label = Label::createWithBMFont("fonts/carterone-20-white.fnt", labelString);
    label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    baseNode->addChild(label);
    
    _icon = Sprite::createWithSpriteFrameName("map_lock.png");
    _icon->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
//    baseNode->addChild(_icon);
    
    _icon->runAction(RepeatForever::create(Sequence::create(RotateBy::create(0.5f, 20, 0),
                                                            RotateBy::create(0.5f, -20, 0),
                                                            nullptr)));
    this->setNormalImage(_icon);
    
    return true;
}


void MapIcon::setLocked(int isLocked){
    _isLocked = isLocked;
    if (_isLocked) {
        _icon->setSpriteFrame("map_lock.png");
    } else {
        _icon->setSpriteFrame("map_key.png");
    }
}

#ifndef __Helpers_H__
#define __Helpers_H__

#include "cocos2d.h"

USING_NS_CC;

// directions
typedef enum GameDirs : unsigned int{
    GameDirNone = 0,
    GameDirUp = 1,
    GameDirDown = 2,
    GameDirLeft = 3,
    GameDirRight = 4
} GameDirs;

class Helpers
{
public:

    static int swipeDirection(Point start, Point end);
    static std::vector<std::string> explodeString(std::string delimiter, std::string  str);
    static bool to_bool(std::string const& s);
};

#endif // __Helpers_H__

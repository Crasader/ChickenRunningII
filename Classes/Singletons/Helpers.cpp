#include "Helpers.h"

int Helpers::swipeDirection(Point start, Point end) {
    const int swipeDist = 15;
    
    float dx = end.x - start.x;
    float dy = end.y - start.y;
    float dist = sqrt(dx*dx + dy*dy);
    if(dist > swipeDist && dx != dy) {
        // left or right
        if(std::abs(dx) > std::abs(dy)) {
            if(dx > 0) {
                return GameDirRight;
            } else {
                return GameDirLeft;
            }
        }
        // up or down
        else {
            if(dy > 0) {
                return GameDirUp;
            } else {
                return GameDirDown;
            }
        }
    }
    return GameDirNone;
}

std::vector<std::string> Helpers::explodeString(std::string delimiter, std::string str) {
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;
    while ((end = str.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(str.substr(start));
    return tokens;
}

bool Helpers::to_bool(std::string const& s) {
    return s != "0";
}

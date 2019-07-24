#include "Level.h"
#include "Helpers.h"

Level::Level()
:_number(0)
,_data("")
,_min_moves(0)
,_complete(false)
,_complete_easy(false)
,_complete_medium(false)
,_complete_hard(false)
,_perfect(false)
{}


Level* Level::createFromString(std::string str) {
    Level* level = new(std::nothrow) Level();
    if (level) {
        level->fromString(str);
        level->autorelease();
        return level;
    } else  {
        delete level;
        level = NULL;
        return NULL;
    }
}

void Level::fromString(std::string str) {
    std::vector<std::string> strings = Helpers::explodeString(";", str);

    _number			= atoi(strings.at(0).c_str());
    _data			= strings.at(1);
    _min_moves		= atoi(strings.at(2).c_str());
    _complete		= atoi(strings.at(3).c_str());
    _complete_easy	= atoi(strings.at(4).c_str());
    _complete_medium = atoi(strings.at(5).c_str());
    _complete_hard	= atoi(strings.at(6).c_str());
    _perfect		= atoi(strings.at(7).c_str());
}

std::string Level::toString() {
    return StringUtils::format("%d;%s;%d;%d;%d;%d;%d;%d", _number, _data.c_str(), _min_moves, _complete, _complete_easy, _complete_medium, _complete_hard, _perfect);
}
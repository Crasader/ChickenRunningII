#include "Achievements.h"

Achievements* Achievements::_instance = nullptr;

Achievements::Achievements()
:_numAchievements(13)
{}

Achievements* Achievements::getInstance() {
    if (_instance == nullptr) {
        _instance = new Achievements();
        _instance->init();
    }
    
    return _instance;
}

void Achievements::init()
{
    log("Achievements init");
    this->load();
}

std::string Achievements::getFilePath() {
    return StringUtils::format("xml/Achievements.plist");
}

void Achievements::load() {
    if (FileUtils::getInstance()->isFileExist(this->getFilePath())) {
        log("Achievements load");
        _achievements = FileUtils::getInstance()->getValueVectorFromFile(this->getFilePath());
        _doorsOpened  = _achievements.at(0).asInt();
        for (int i = 1; i <= _numAchievements; i++)
            _achieved.push_back(_achievements.at(i).asInt());
    } else {
        log("Achievements create new file");
        _doorsOpened	= 0;
        for (int i = 1; i <= _numAchievements; i++)
            _achieved.push_back(0);
        this->save();
    }
}

void Achievements::save() {
    log("Achievements save");
    _achievements.clear();
    _achievements.push_back(Value(_doorsOpened));
    for (int i=0; i < _numAchievements; i++)
        _achievements.push_back(Value(_achieved.at(i)));
    if (FileUtils::getInstance()->writeValueVectorToFile(_achievements, this->getFilePath())) {
        log("Achievements wrote file");
    } else log("Achievements file not written");
}

void Achievements::reset() {
    _achieved.clear();
    for (int i = 1; i <= _numAchievements; i++)
        _achieved.push_back(0);
    this->save();
}

bool Achievements::unlock(int achievementId) {
    if (_achieved.at(achievementId) == 1) return false;
    _achieved.at(achievementId) = 1;
    this->save();
    return true;
}

std::string Achievements::getName(int i) {
    switch(i) {
        case 0: return ACHIEVEMENT0_NAME;
        case 1: return ACHIEVEMENT1_NAME;
        case 2: return ACHIEVEMENT2_NAME;
        case 3: return ACHIEVEMENT3_NAME;
        case 4: return ACHIEVEMENT4_NAME;
        case 5: return ACHIEVEMENT5_NAME;
        case 6: return ACHIEVEMENT6_NAME;
        case 7: return ACHIEVEMENT7_NAME;
        case 8: return ACHIEVEMENT8_NAME;
        case 9: return ACHIEVEMENT9_NAME;
        case 10: return ACHIEVEMENT10_NAME;
        case 11: return ACHIEVEMENT11_NAME;
        case 12: return ACHIEVEMENT12_NAME;
    }
    return "";
}

std::string Achievements::getDescription(int i) {
    switch(i) {
        case 0: return ACHIEVEMENT0_DESC;
        case 1: return ACHIEVEMENT1_DESC;
        case 2: return ACHIEVEMENT2_DESC;
        case 3: return ACHIEVEMENT3_DESC;
        case 4: return ACHIEVEMENT4_DESC;
        case 5: return ACHIEVEMENT5_DESC;
        case 6: return ACHIEVEMENT6_DESC;
        case 7: return ACHIEVEMENT7_DESC;
        case 8: return ACHIEVEMENT8_DESC;
        case 9: return ACHIEVEMENT9_DESC;
        case 10: return ACHIEVEMENT10_DESC;
        case 11: return ACHIEVEMENT11_DESC;
        case 12: return ACHIEVEMENT12_DESC;
    }
    return "";
}



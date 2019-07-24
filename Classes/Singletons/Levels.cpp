#include "Levels.h"
#include "Helpers.h"

Levels* Levels::_instance = nullptr;

Levels* Levels::getInstance() {
    if (_instance == nullptr) {
        _instance = new Levels();
        _instance->init();
    }
    
    return _instance;
}

void Levels::init()
{
    log("Level init");
    auto filePath = FileUtils::getInstance()->getWritablePath();
    _filename = filePath + "Levels.plist";
    this->load();
}

void Levels::load() {
    bool fileExists = FileUtils::getInstance()->isFileExist(_filename);
    if(fileExists) {
        log("Levels load");
        ValueVector levelsStrVector = FileUtils::getInstance()->getValueVectorFromFile(_filename);

        for(int i = 0; i < levelsStrVector.size(); i++) {
            auto level = Level::createFromString(levelsStrVector.at(i).asString());
            _levels.pushBack(level);
        }
    } else {
        log("Levels create new file");
        this->reset();
    }
}

void Levels::save() {
    log("Levels save");
    ValueVector levelsStrVector;
    for(int i = 0; i < _levels.size(); i++) {
        auto l = (Level*) _levels.at(i);
        std::string str = l->toString();
        log("%d %s", i, str.c_str());
        levelsStrVector.push_back(Value(str));
    }
    if (FileUtils::getInstance()->writeValueVectorToFile(levelsStrVector, _filename)) {
        log("Levels wrote file");
    } else log("Levels file not written");
}

void Levels::reset() {
    log("Levels reset level data");
    std::string levelsStr = FileUtils::getInstance()->getStringFromFile("xml/levels.txt");
    std::vector<std::string> levelsStrVector = Helpers::explodeString("\n", levelsStr);
    for (int i = 0; i < levelsStrVector.size(); i++) {
        if (levelsStrVector.at(i).length() > 0) {
            auto level = Level::createFromString(levelsStrVector.at(i));
            _levels.pushBack(level);
        }
    }

    this->save();
}

void Levels::markAsPerfect(int level, int perfect) {
    auto l = (Level*) _levels.at(level - 1);
    l->setPerfect(perfect);
    this->save();
}

int Levels::perfectLevels() {
    int perfectCount = 0;
    for (int i = 0; i < _levels.size(); i++) {
        Level* l = (Level*) _levels.at(i);
        if (l->getPerfect()) perfectCount ++;//s= l->getPerfect();
    }
    return perfectCount;
}

bool Levels::isComplete(int level) {
    return ((Level*)_levels.at(level - 1))->getComplete();
}

Vector<Level*> Levels::getLevels() {
    return _levels;
}

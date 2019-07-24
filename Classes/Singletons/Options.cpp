#include "Options.h"

Options* Options::_instance = nullptr;

Options::Options()
:sound(1)
,music(1)
,shake(1)
,difficulty(1)
,loadCount(0)
{}

Options* Options::getInstance() {
    if (_instance == nullptr) {
        _instance = new Options();
        _instance->init();
    }
    
    return _instance;
}

void Options::init()
{
    this->load();
}

void Options::load() {
    sound		= UserDefault::getInstance()->getIntegerForKey("options_sound", 1);
    music		= UserDefault::getInstance()->getIntegerForKey("options_music", 1);
    shake		= UserDefault::getInstance()->getIntegerForKey("options_shake", 1);
    difficulty	= UserDefault::getInstance()->getIntegerForKey("options_difficulty", 1);
    loadCount	= UserDefault::getInstance()->getIntegerForKey("options_loadCount", 0);

    loadCount++;
    this->save();
}

void Options::save() {
    log("Options save");
    UserDefault::getInstance()->setIntegerForKey("options_sound", sound);
    UserDefault::getInstance()->setIntegerForKey("options_music", music);
    UserDefault::getInstance()->setIntegerForKey("options_shake", shake);
    UserDefault::getInstance()->setIntegerForKey("options_difficulty", difficulty);
    UserDefault::getInstance()->setIntegerForKey("options_loadcount", loadCount);
}

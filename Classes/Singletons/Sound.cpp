#include "Sound.h"
#include "SimpleAudioEngine.h" 

using namespace CocosDenshion;

Sound* Sound::_instance = nullptr;

Sound* Sound::getInstance() {
    if (_instance == nullptr) {
        _instance = new Sound();
        _instance->init();
    }
    
    return _instance;
}

void Sound::init()
{
    log("Sound init");
    _options = Options::getInstance();
    _gameplayPlaying = false;
}


void Sound::play(const char* sound) {
    if (_options->sound) {
        SimpleAudioEngine::getInstance()->playEffect(sound);
    }
}

void Sound::playBackgroundMusic(const char* sound) {
    if (_options->music) {
        SimpleAudioEngine::getInstance()->playBackgroundMusic(sound);
    }
}


void Sound::playKeyMove() {
    this->play("sound/key_move.wav");
}

void Sound::playOpenChest() {
    this->play("sound/open_chest.wav");
}

void Sound::playRestartLevel() {
    this->play("sound/restart_level.wav");
}

void Sound::playDoor() {
    this->play("sound/door.wav");
}

void Sound::playClick() {
    this->play("sound/click.wav");
}

void Sound::playMapLocked() {
    this->play("sound/map_locked.wav");
}

void Sound::playUnlockAchievement() {
    this->play("sound/unlock_achievement.wav");
}

void Sound::startMusicMenu() {
    if (_options->music) {
        _gameplayPlaying = false;
        SimpleAudioEngine::getInstance()->playBackgroundMusic("music/menu.mp3");
    }
}

void Sound::startMusicGameplay() {
    if (!_options->music) return;
    
    this->stopMusic();
    _gameplayPlaying = true;
    
    int randomSong = _gameplayMusicNum;
    while(randomSong == _gameplayMusicNum)
        randomSong = CCRANDOM_0_1() * 3;
        
    std::string song;
    switch(randomSong) {
        default:
        case 0: song = "music/gameplay1.mp3"; break;
        case 1: song = "music/gameplay2.mp3"; break;
        case 2: song = "music/gameplay3.mp3"; break;
    }
    SimpleAudioEngine::getInstance()->playBackgroundMusic(song.c_str());
}

void Sound::stopMusic() {
    _gameplayPlaying = false;
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

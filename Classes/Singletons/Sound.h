#ifndef __SOUND_H__
#define __SOUND_H__

#include "cocos2d.h"
#include "Options.h"

USING_NS_CC;

class Sound
{
public:
    static Sound* getInstance();

    
    void playKeyMove();
    void playOpenChest();
    void playRestartLevel() ;
    void playDoor();
    void playClick();
    void playMapLocked();
    void playUnlockAchievement();
    void startMusicMenu() ;
    void startMusicGameplay();
    void stopMusic();
private:
    static Sound * _instance;
    
    bool _gameplayPlaying;
    int _gameplayMusicNum;
    int _gameplayStart;
    Options* _options;
    
    void init();
    void play(const char* sound);
    void playBackgroundMusic(const char* sound);
};

#endif // __SOUND_H__

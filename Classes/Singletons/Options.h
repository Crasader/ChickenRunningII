#ifndef __Options_H__
#define __Options_H__

#include "cocos2d.h"

USING_NS_CC;

class Options : public Ref
{
public:
    Options();
    
    static Options* getInstance();
    void load();
    void save();
    
    //for effect voice
    unsigned int sound;
    //for background music
    unsigned int music;
    unsigned int shake;
    unsigned int difficulty;
    unsigned int loadCount;
    
private:
    static Options * _instance;
    void init();

    



};

#endif // __Options_H__

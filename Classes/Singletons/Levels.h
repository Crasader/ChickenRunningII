#ifndef __Levels_H__
#define __Levels_H__

#include "cocos2d.h"
#include "Level.h"

USING_NS_CC;

class Levels
{
public:
    static Levels* getInstance();
    
    bool isComplete(int level);
    void markAsPerfect(int level, int perfect);
    int perfectLevels();
    
    void save();
    void reset();
    
    Vector<Level*> getLevels();

private:
    static Levels * _instance;
    
    Vector<Level*> _levels;
    
    void init();
    void load();


    
    std::string _filename;
};

#endif // __Levels_H__

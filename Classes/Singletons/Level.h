#ifndef __Level_H__
#define __Level_H__

#include "cocos2d.h"

USING_NS_CC;

class Level : public Ref
{
public:
    Level();
    
    static Level* createFromString(std::string str);
    std::string toString();
private:
    CC_SYNTHESIZE(int, _number, Number);
    CC_SYNTHESIZE(std::string, _data, Data);
    CC_SYNTHESIZE(int, _min_moves, MinMoves);
    CC_SYNTHESIZE(bool, _complete, Complete);
    CC_SYNTHESIZE(bool, _complete_easy, CompleteEasy);
    CC_SYNTHESIZE(bool, _complete_medium, CompleteMedium);
    CC_SYNTHESIZE(bool, _complete_hard, CompleteHard);
    CC_SYNTHESIZE(int, _perfect, Perfect);
    
    void fromString(std::string str);
};


#endif // __Level_H__

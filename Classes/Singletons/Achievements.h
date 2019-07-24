#ifndef __Achievements_H__
#define __Achievements_H__

#include "cocos2d.h"

USING_NS_CC;

// the achievements
typedef enum {
    AchievementBeginTheHunt = 0,
    AchievementKnockKnock = 1,
    AchievementTheDoorman = 2,
    AchievementTheDoorToKnowhere = 3,
    AchievementPerfectionist = 4,
    AchievementProfessionalPerfectionist = 5,
    AchievementEnterTheDarkness = 6,
    AchievementEnjoyTheSun = 7,
    AchievementArrrgh = 8,
    AchievementTreasureHunter = 9,
    AchievementAnAdventurerIsYou = 10,
    AchievementIntrepidExplorer = 11,
    AchievementMastermind = 12
} AchievementNames;

#define ACHIEVEMENT0_NAME "Begin the Hunt"
#define ACHIEVEMENT0_DESC "Beat the first 10 levels"
#define ACHIEVEMENT1_NAME "Knock Knock"
#define ACHIEVEMENT1_DESC "Open a door"
#define ACHIEVEMENT2_NAME "The Doorman"
#define ACHIEVEMENT2_DESC "Open 50 doors"
#define ACHIEVEMENT3_NAME "The Door to Nowhere"
#define ACHIEVEMENT3_DESC "Can you find it?"
#define ACHIEVEMENT4_NAME "Perfectionist"
#define ACHIEVEMENT4_DESC "Play any 10 levels perfectly"
#define ACHIEVEMENT5_NAME "Professional Perfectionist"
#define ACHIEVEMENT5_DESC "Play any 30 levels perfectly"
#define ACHIEVEMENT6_NAME "Enter the Darkness"
#define ACHIEVEMENT6_DESC "Make it to the Caves"
#define ACHIEVEMENT7_NAME "Enjoy the Sun"
#define ACHIEVEMENT7_DESC "Make it to the Beach"
#define ACHIEVEMENT8_NAME "Arrrgh!"
#define ACHIEVEMENT8_DESC "Make it to the Pirate Ship"
#define ACHIEVEMENT9_NAME "Treasure Hunter"
#define ACHIEVEMENT9_DESC "Beat all level on Easy"
#define ACHIEVEMENT10_NAME "An Adventurer is You"
#define ACHIEVEMENT10_DESC "Beat all levels on Medium"
#define ACHIEVEMENT11_NAME "Intrepid Explorer"
#define ACHIEVEMENT11_DESC "Beat all levels on Hard"
#define ACHIEVEMENT12_NAME "Mastermind"
#define ACHIEVEMENT12_DESC "Beat all levels perfectly"

#define ACHIEVEMENT_NUM 13

class Achievements : public Ref
{
public:
    Achievements();
    
    static Achievements* getInstance();

    std::string getName(int i);
    std::string getDescription(int i);
    
private:
    static Achievements * _instance;
    
    CC_SYNTHESIZE(int, _doorsOpened, DoorsOpened);
    CC_SYNTHESIZE(int, _numAchievements, NumAchievements);
    CC_SYNTHESIZE(std::vector<int>, _achieved, Achieved);
    ValueVector _achievements;

    void init();
    std::string getFilePath();
    void load();
    
    void save();
    void reset();
    bool unlock(int achievementId);
};

#endif // __Achievements_H__

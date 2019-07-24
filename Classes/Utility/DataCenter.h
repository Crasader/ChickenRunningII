#ifndef __DataCenter_H__
#define __DataCenter_H__

#include "cocos2d.h"

USING_NS_CC;

class DataCenter
{
public:
    static DataCenter *getInstance();
    void setValueVectorForKey(ValueVector &vector, const char *key);
    ValueVector getValueVectorByKey(const char *key);
private:
    static DataCenter *_dataCenter;

};


#endif // __DataCenter_H__

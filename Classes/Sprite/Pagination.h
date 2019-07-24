//
//  Pagination.hpp
//  LetMeOut
//
//  Created by kangbiao on 16/1/22.
//
//

#ifndef Pagination_hpp
#define Pagination_hpp

#include "cocos2d.h"

USING_NS_CC;

class Pagination : public Sprite
{
public:

    static Pagination * create(int maxPageNum);
    bool init(int maxPageNum);
    
    void setCurrentPaginationPosition(int currentPageNum);
    Size getPaginationContentSize();
private:
    int _maxPageNum;
    int _currentPageNum;
    Size _size;
    Vector<Sprite *> _paginationVector;

    void initPagination();
    
};

#endif /* Pagination_hpp */

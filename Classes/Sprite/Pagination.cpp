//
//  Pagination.cpp
//  LetMeOut
//
//  Created by kangbiao on 16/1/22.
//
//

#include "Pagination.h"

Pagination * Pagination::create(int maxPageNum) {
    auto pRet = new Pagination();

    if (pRet->init(maxPageNum)) {
        pRet->autorelease();
    } else {
        delete pRet;
        return nullptr;
    }
    
    return pRet;
}

bool  Pagination::init(int maxPageNum) {
    if ( !Sprite::init() )
    {
        return false;
    }
    _maxPageNum = maxPageNum;
    _currentPageNum = 0;
    
    this->initPagination();
    
    return true;
}

void Pagination::initPagination() {
    auto pagination = Sprite::createWithSpriteFrameName("select_level_pagination_active.png");
    _size = Size(pagination->getContentSize().width * 2 * _maxPageNum,
                 pagination->getContentSize().height);
    for (int i = 0; i < _maxPageNum; i++) {
        auto tempPagination = Sprite::createWithSpriteFrameName("select_level_pagination_inactive.png");
        tempPagination->setPosition( -_size.width / 2 + tempPagination->getContentSize().width * (2.0f * i - 0.5f),
                                    0);
        _paginationVector.pushBack(tempPagination);
        this->addChild(tempPagination);
    }
}

Size Pagination::getPaginationContentSize() {
    return _size;
}

void Pagination::setCurrentPaginationPosition(int currentPageNum) {
    _paginationVector.at(_currentPageNum)->setSpriteFrame("select_level_pagination_inactive.png");
    _paginationVector.at(currentPageNum)->setSpriteFrame("select_level_pagination_active.png");
    _currentPageNum = currentPageNum;
}
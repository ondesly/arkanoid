//
//  Block.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 03.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include "Block.h"

ar::Block *ar::Block::createWithSpriteFrameName(const std::string &name, size_t type) {
    auto block = new(std::nothrow) Block();
    if (block && block->initWithSpriteFrameName(name, type)) {
        block->autorelease();
        return block;
    }
    CC_SAFE_DELETE(block);
    return nullptr;
}

bool ar::Block::initWithSpriteFrameName(const std::string &name, size_t type) {
    if (!RectangleBody::initWithSpriteFrameName(name)) {
        return false;
    }

    setType(type);

    return true;
}

void ar::Block::setType(size_t type) {
    mType = type;

    switch (type) {
        case 0:
            setColor(cocos2d::Color3B::GREEN);
            break;
        case 1:
            setColor(cocos2d::Color3B::RED);
            break;
        case 2:
            setColor(cocos2d::Color3B::BLUE);
            break;
        default:
            setVisible(false);
            break;
    }
}

void ar::Block::onCollision() {
    setType(--mType);
}

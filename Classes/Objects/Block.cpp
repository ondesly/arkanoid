//
//  Block.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 03.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include "Block.h"

namespace {

    const cocos2d::Color3B cRed{255, 0, 0};
    const cocos2d::Color3B cGreen{0, 255, 0};
    const cocos2d::Color3B cBlue{0, 112, 255};

}

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

    setColor(getColor(type));
    setVisible(type < 3);
}

void ar::Block::onCollision() {
    setType(--mType);
}

const cocos2d::Color3B &ar::Block::getColor(size_t type) const {
    switch (type) {
        case 0:
            return cGreen;
        case 1:
            return cRed;
        case 2:
            return cBlue;
        default:
            return cocos2d::Color3B::WHITE;
    }
}

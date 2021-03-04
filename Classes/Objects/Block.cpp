//
//  Block.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 03.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <base/CCEventDispatcher.h>

#include "Resources.h"

#include "Block.h"

namespace {

    const cocos2d::Color3B cRed{255, 0, 0};
    const cocos2d::Color3B cGreen{0, 255, 0};
    const cocos2d::Color3B cBlue{0, 112, 255};

}

ar::Block *ar::Block::createWithSpriteFrameName(const std::string &name, int type) {
    auto block = new(std::nothrow) Block();
    if (block && block->initWithSpriteFrameName(name, type)) {
        block->autorelease();
        return block;
    }
    CC_SAFE_DELETE(block);
    return nullptr;
}

bool ar::Block::initWithSpriteFrameName(const std::string &name, int type) {
    if (!RectangleBody::initWithSpriteFrameName(name)) {
        return false;
    }

    //

    auto shadow = cocos2d::Sprite::createWithSpriteFrameName(texture::game::empty);
    shadow->setColor(cocos2d::Color3B::BLACK);
    shadow->setOpacity(cShadowOpacity);
    shadow->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    shadow->setPosition({getContentSize().width / 2, -getContentSize().height});
    shadow->setScale(
            getContentSize().width / shadow->getContentSize().width,
            getContentSize().height / shadow->getContentSize().height);
    addChild(shadow);

    //

    setType(type);

    //

    return true;
}

void ar::Block::setType(int type) {
    mType = type;

    setColor(getColor(type));
    setVisible(type >= 0);
}

void ar::Block::onCollision() {
    setType(--mType);

    if (mType < 0) {
        getEventDispatcher()->dispatchCustomEvent(event::onBlockDestroyed);
    }
}

const cocos2d::Color3B &ar::Block::getColor(int type) const {
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

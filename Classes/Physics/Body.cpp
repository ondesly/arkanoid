//
//  Body.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include "Body.h"

ar::Body *ar::Body::create() {
    auto body = new(std::nothrow) Body();

const cocos2d::Vec2 &ar::Body::getVelocity() const {
    return mVelocity;
}

void ar::Body::setVelocity(const cocos2d::Vec2 &velocity) {
    mVelocity = velocity;
}
    if (body && body->init()) {
        body->autorelease();
        return body;
    }
    CC_SAFE_DELETE(body);
    return nullptr;
}

bool ar::Body::init() {
    if (!Sprite::init()) {
        return false;
    }

    setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);

    return true;
}
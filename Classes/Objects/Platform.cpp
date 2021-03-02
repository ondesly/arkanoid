//
//  Platform.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include "Platform.h"

namespace {

    const float cFriction = 0.5F;
    const float cVelocity = 5.F;

    constexpr float get_sign(float value) {
        return (0.F < value) - (value < 0.F);
    }

}

ar::Platform *ar::Platform::create() {
    auto platform = new(std::nothrow) Platform();
    if (platform && platform->init()) {
        platform->autorelease();
        return platform;
    }
    CC_SAFE_DELETE(platform);
    return nullptr;
}

bool ar::Platform::init() {
    if (!RectangleBody::init()) {
        return false;
    }

    setFriction(cFriction);

    scheduleUpdate();

    return true;
}

void ar::Platform::update(float delta) {
    Node::update(delta);

    if ((getPosition().x == mTargetX) ||
            (getVelocity().x > 0.F && getPosition().x > mTargetX) ||
            (getVelocity().x < 0.F && getPosition().x < mTargetX)) {
        setVelocity(cocos2d::Vec2::ZERO);
    }
}

void ar::Platform::setTargetX(float x) {
    mTargetX = x;

    setVelocity({cVelocity * get_sign(mTargetX - getPosition().x), 0.F});
}
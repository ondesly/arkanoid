//
//  Platform.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include "Platform.h"

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

    scheduleUpdate();

    return true;
}

void ar::Platform::update(float delta) {
    Node::update(delta);

    if ((getPosition().x == mTargetX) ||
            (getVelocity().x > 0.F && getPosition().x > mTargetX) ||
            (getVelocity().x < 0.F && getPosition().x < mTargetX)) {
        setVelocity({});
    }
}

void ar::Platform::setTargetX(float x) {
    mTargetX = x;

    setVelocity({mTargetX > getPosition().x ? 1.F : -1.F, 0.F});
}
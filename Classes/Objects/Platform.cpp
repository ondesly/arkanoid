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

void ar::Platform::setTargetX(float x) {
    mTargetX = x;

    setVelocity({mTargetX > getPosition().x ? 1.F : -1.F, 0.F});
}

void ar::Platform::setPosition(const cocos2d::Vec2 &pos) {
    Sprite::setPosition(pos);

    if ((pos.x == mTargetX) ||
            (mVelocity.x > 0.F && pos.x > mTargetX) ||
            (mVelocity.x < 0.F && pos.x < mTargetX)) {
        setVelocity({});
    }
}

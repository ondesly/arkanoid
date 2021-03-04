//
//  RectangleBody.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 04.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include "RectangleBody.h"

ar::RectangleBody *ar::RectangleBody::create() {
    auto body = new(std::nothrow) RectangleBody();
    if (body && body->init()) {
        body->autorelease();
        return body;
    }
    CC_SAFE_DELETE(body);
    return nullptr;
}

ar::RectangleBody *ar::RectangleBody::createWithSpriteFrameName(const std::string &name) {
    auto body = new(std::nothrow) RectangleBody();
    if (body && body->initWithSpriteFrameName(name)) {
        body->autorelease();
        return body;
    }
    CC_SAFE_DELETE(body);
    return nullptr;
}

bool ar::RectangleBody::isCollided(ar::Body *obstacle) const {
    return false;
}

cocos2d::Vec2 ar::RectangleBody::getVelocityAfterCollision(ar::Body *obstacle) const {
    return {};
}
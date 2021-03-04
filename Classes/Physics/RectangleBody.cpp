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
    const auto rect = getVisibleRect();
    const auto obRect = obstacle->getVisibleRect();

    return rect.size.width >= obRect.origin.x && rect.origin.x <= obRect.size.width &&
            rect.size.height >= obRect.origin.y && rect.origin.y <= obRect.size.height;
}

cocos2d::Vec2 ar::RectangleBody::getVelocityAfterCollision(ar::Body *obstacle) const {
    const auto pos = getPosition();
    const auto &velocity = getVelocity();
    const auto rect = obstacle->getVisibleRect();

    auto result = velocity;

    // Horizontal

    if (pos.x < rect.origin.x) {
        result.x = -std::abs(result.x);
    } else if (pos.x > rect.size.width) {
        result.x = std::abs(result.x);
    }

    // Vertical

    if (pos.y < rect.origin.y) {
        result.y = -std::abs(result.y);
    } else if (pos.y > rect.size.height) {
        result.y = std::abs(result.y);
    }

    //

    return result;
}
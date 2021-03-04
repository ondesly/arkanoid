//
//  CircleBody.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 04.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include "CircleBody.h"

ar::CircleBody *ar::CircleBody::create() {
    auto body = new(std::nothrow) CircleBody();
    if (body && body->init()) {
        body->autorelease();
        return body;
    }
    CC_SAFE_DELETE(body);
    return nullptr;
}

ar::CircleBody *ar::CircleBody::createWithSpriteFrameName(const std::string &name) {
    auto body = new(std::nothrow) CircleBody();
    if (body && body->initWithSpriteFrameName(name)) {
        body->autorelease();
        return body;
    }
    CC_SAFE_DELETE(body);
    return nullptr;
}

bool ar::CircleBody::isCollided(ar::Body *obstacle) const {
    const auto &pos = getPosition();
    const auto rect = obstacle->getVisibleRect();

    const cocos2d::Vec2 nearest{
            std::max(std::min(pos.x, rect.size.width), rect.origin.x),
            std::max(std::min(pos.y, rect.size.height), rect.origin.y)};

    const auto distance = pos.getDistance(nearest);
    return distance <= getContentSize().width / 2;
}

cocos2d::Vec2 ar::CircleBody::getVelocityAfterCollision(ar::Body *obstacle) const {
    const auto &pos = getPosition();
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
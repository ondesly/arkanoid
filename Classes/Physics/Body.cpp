//
//  Body.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include "Body.h"

bool ar::Body::init() {
    if (!Sprite::init()) {
        return false;
    }

    return true;
}

float ar::Body::getSpeed() const {
    return mSpeed;
}

void ar::Body::setSpeed(float speed) {
    mSpeed = speed;
}

const cocos2d::Vec2 &ar::Body::getVelocity() const {
    return mVelocity;
}

void ar::Body::setVelocity(const cocos2d::Vec2 &velocity) {
    mVelocity = velocity;
}

float ar::Body::getFriction() const {
    return mFriction;
}

void ar::Body::setFriction(float friction) {
    mFriction = friction;
}

ar::RectangleBody *ar::RectangleBody::create() {
    auto body = new(std::nothrow) RectangleBody();
    if (body && body->init()) {
        body->autorelease();
        return body;
    }
    CC_SAFE_DELETE(body);
    return nullptr;
}

cocos2d::Vec2 ar::RectangleBody::getCollisionResult(ar::Body *obstacle) const {
    return {};
}

ar::CircleBody *ar::CircleBody::create() {
    auto body = new(std::nothrow) CircleBody();
    if (body && body->init()) {
        body->autorelease();
        return body;
    }
    CC_SAFE_DELETE(body);
    return nullptr;
}

cocos2d::Vec2 ar::CircleBody::getCollisionResult(ar::Body *obstacle) const {
    const auto &pos = getPosition();
    const auto obstaclePos = obstacle->getPosition() - obstacle->getContentSize() / 2;
    const auto &obstacleSize = obstacle->getContentSize();

    cocos2d::Vec2 nearest = pos;
    cocos2d::Vec2 result{1.F, 1.F};

    // Horizontal

    if (pos.x < obstaclePos.x) {
        nearest.x = obstaclePos.x;
        result.x = -1.F;
    } else if (pos.x > obstaclePos.x + obstacleSize.width) {
        nearest.x = obstaclePos.x + obstacleSize.width;
        result.x = -1.F;
    }

    // Vertical

    if (pos.y < obstaclePos.y) {
        nearest.y = obstaclePos.y;
        result.y = -1.F;
    } else if (pos.y > obstaclePos.y + obstacleSize.height) {
        nearest.y = obstaclePos.y + obstacleSize.height;
        result.y = -1.F;
    }

    // Distance

    const cocos2d::Vec2 diff = pos - nearest;
    const float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

    if (distance <= getContentSize().width / 2) {
        return result;
    } else {
        return {};
    }
}
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

bool ar::RectangleBody::isCollided(ar::Body *obstacle) const {
    return false;
}

cocos2d::Vec2 ar::RectangleBody::getCollisionVelocity(ar::Body *obstacle) const {
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

bool ar::CircleBody::isCollided(ar::Body *obstacle) const {
    const auto &pos = getPosition();
    const auto &obstacleSize = obstacle->getContentSize();
    const auto obstaclePos = obstacle->getPosition() - obstacleSize / 2;

    const cocos2d::Vec2 nearest{
            std::max(std::min(pos.x, obstaclePos.x + obstacleSize.width), obstaclePos.x),
            std::max(std::min(pos.y, obstaclePos.y + obstacleSize.height), obstaclePos.y)};

    const auto distance = pos.getDistance(nearest);
    return distance <= getContentSize().width / 2;
}

cocos2d::Vec2 ar::CircleBody::getCollisionVelocity(ar::Body *obstacle) const {
    const auto &pos = getPosition();
    const auto &velocity = getVelocity();
    const auto obstaclePos = obstacle->getPosition() - obstacle->getContentSize() / 2;
    const auto &obstacleSize = obstacle->getContentSize();

    cocos2d::Vec2 nearest = pos;
    cocos2d::Vec2 result;

    // Horizontal

    if (pos.x < obstaclePos.x) {
        nearest.x = obstaclePos.x;
        result.x = -velocity.x * 2;
    } else if (pos.x > obstaclePos.x + obstacleSize.width) {
        nearest.x = obstaclePos.x + obstacleSize.width;
        result.x = -velocity.x * 2;
    }

    // Vertical

    if (pos.y < obstaclePos.y) {
        nearest.y = obstaclePos.y;
        result.y = -velocity.y * 2;
    } else if (pos.y > obstaclePos.y + obstacleSize.height) {
        nearest.y = obstaclePos.y + obstacleSize.height;
        result.y = -velocity.y * 2;
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
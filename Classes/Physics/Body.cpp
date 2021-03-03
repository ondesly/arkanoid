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

void ar::Body::updatePosition() {
    setPosition(getPosition() + mVelocity * mSpeed);
}

void ar::Body::updateVelocityAfterCollision(ar::Body *obstacle) {
    const auto velocity = getVelocityAfterCollision(obstacle);

    const auto &ob_velocity = obstacle->getVelocity();
    const auto ob_friction = obstacle->getFriction();

    const auto new_velocity = velocity + ob_velocity * ob_friction;
    setVelocity(new_velocity.getNormalized());
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

cocos2d::Vec2 ar::RectangleBody::getVelocityAfterCollision(ar::Body *obstacle) const {
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

cocos2d::Vec2 ar::CircleBody::getVelocityAfterCollision(ar::Body *obstacle) const {
    const auto &pos = getPosition();
    const auto &velocity = getVelocity();
    const auto &obstacleSize = obstacle->getContentSize();
    const auto obstaclePos = obstacle->getPosition() - obstacleSize / 2;

    auto result = velocity;

    // Horizontal

    if (pos.x < obstaclePos.x) {
        result.x = -std::abs(result.x);
    } else if (pos.x > obstaclePos.x + obstacleSize.width) {
        result.x = std::abs(result.x);
    }

    // Vertical

    if (pos.y < obstaclePos.y) {
        result.y = -std::abs(result.y);
    } else if (pos.y > obstaclePos.y + obstacleSize.height) {
        result.y = std::abs(result.y);
    }

    //

    return result;
}
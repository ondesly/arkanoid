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

cocos2d::Rect ar::Body::getVisibleRect() const {
    const auto &transform = getNodeToParentTransform();

    cocos2d::Vec3 p0;
    transform.transformPoint(&p0);

    cocos2d::Vec3 p1{getContentSize().width, getContentSize().height, 0.F};
    transform.transformPoint(&p1);

    return {std::min(p0.x, p1.x), std::min(p0.y, p1.y), std::max(p0.x, p1.x), std::max(p0.y, p1.y)};
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

void ar::Body::onCollision() {

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
//
//  Body.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include "Body.h"

cocos2d::Rect ar::Body::getVisibleRect() {
    if (mIsVisibleRectDirty) {
        const auto &transform = getNodeToParentTransform();

        cocos2d::Vec3 p0;
        transform.transformPoint(&p0);

        cocos2d::Vec3 p1{getContentSize().width, getContentSize().height, 0.F};
        transform.transformPoint(&p1);

        mVisibleRect = {std::min(p0.x, p1.x), std::min(p0.y, p1.y), std::max(p0.x, p1.x), std::max(p0.y, p1.y)};
        mIsVisibleRectDirty = false;
    }

    return mVisibleRect;
}

void ar::Body::updatePosition() {
    setPosition(getPosition() + mVelocity * mSpeed);
    mIsVisibleRectDirty = true;
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
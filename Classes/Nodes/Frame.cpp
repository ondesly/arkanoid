//
//  Frame.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 04.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <2d/CCSpriteFrameCache.h>

#include "Physics/RectangleBody.h"
#include "Physics/Physics.h"
#include "Resources.h"

#include "Frame.h"

ar::Frame *ar::Frame::create(const std::shared_ptr<Physics> &physics) {
    auto emptyFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(texture::game::empty);

    auto frame = new(std::nothrow) Frame(physics);
    if (frame && frame->initWithTexture(emptyFrame->getTexture())) {
        frame->autorelease();
        return frame;
    }
    CC_SAFE_DELETE(frame);
    return nullptr;
}

ar::Frame::Frame(const std::shared_ptr<Physics> &physics) : mPhysics(physics) {

}

void ar::Frame::setContentSize(const cocos2d::Size &contentSize) {
    Node::setContentSize(contentSize);

    layout();
}

void ar::Frame::layout() {
    addTop();
    addSides();
}

void ar::Frame::addTop() {
    auto cornerFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(texture::game::tubeCornerLeft);
    auto decorFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(texture::game::tubeDecor);

    const auto cornerWidth = cornerFrame->getOriginalSize().width;
    const auto segmentSize = (getContentSize().width - cornerWidth * 2 - decorFrame->getOriginalSize().width * 2) / 4;

    mBorder = cornerWidth;

    // Corners

    auto cornerLeft = RectangleBody::createWithSpriteFrameName(texture::game::tubeCornerLeft);
    cornerLeft->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    cornerLeft->setPosition({0.F, getContentSize().height});
    addChild(cornerLeft);
    mPhysics->registerObstacle(cornerLeft);

    auto cornerRight = RectangleBody::createWithSpriteFrameName(texture::game::tubeCornerRight);
    cornerRight->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_RIGHT);
    cornerRight->setPosition({getContentSize().width, getContentSize().height});
    addChild(cornerRight);
    mPhysics->registerObstacle(cornerRight);

    // Tube H

    auto tubeHLeft = RectangleBody::createWithSpriteFrameName(texture::game::tube);
    tubeHLeft->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    tubeHLeft->setPosition({cornerWidth, getContentSize().height});
    tubeHLeft->setScaleX(segmentSize / tubeHLeft->getContentSize().width);
    addChild(tubeHLeft);
    mPhysics->registerObstacle(tubeHLeft);

    auto tubeHCenter = RectangleBody::createWithSpriteFrameName(texture::game::tube);
    tubeHCenter->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
    tubeHCenter->setPosition({getContentSize().width / 2, getContentSize().height});
    tubeHCenter->setScaleX(segmentSize * 2 / tubeHCenter->getContentSize().width);
    addChild(tubeHCenter);
    mPhysics->registerObstacle(tubeHCenter);

    auto tubeHRight = RectangleBody::createWithSpriteFrameName(texture::game::tube);
    tubeHRight->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_RIGHT);
    tubeHRight->setPosition({getContentSize().width - cornerWidth, getContentSize().height});
    tubeHRight->setScaleX(segmentSize / tubeHRight->getContentSize().width);
    addChild(tubeHRight);
    mPhysics->registerObstacle(tubeHRight);

    // Decor

    auto decorLeft = RectangleBody::createWithSpriteFrameName(texture::game::tubeDecor);
    decorLeft->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    decorLeft->setPosition({cornerWidth + segmentSize, getContentSize().height});
    addChild(decorLeft);
    mPhysics->registerObstacle(decorLeft);

    auto decorRight = RectangleBody::createWithSpriteFrameName(texture::game::tubeDecor);
    decorRight->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_RIGHT);
    decorRight->setPosition({getContentSize().width - segmentSize - cornerWidth, getContentSize().height});
    addChild(decorRight);
    mPhysics->registerObstacle(decorRight);
}

void ar::Frame::addSides() {
    auto cornerFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(texture::game::tubeCornerLeft);
    auto decorFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(texture::game::tubeDecor);

    const auto top = getContentSize().height - cornerFrame->getOriginalSize().height;
    const auto segmentSize = decorFrame->getOriginalSize().width;
    const auto segmentsCount = size_t(std::ceil(top / segmentSize));

    for (size_t i = 0; i < segmentsCount; ++i) {
        RectangleBody *left;
        RectangleBody *right;

        if (i % 2 == 0) {
            left = RectangleBody::createWithSpriteFrameName(texture::game::tubeDecor);
            right = RectangleBody::createWithSpriteFrameName(texture::game::tubeDecor);
        } else {
            left = RectangleBody::createWithSpriteFrameName(texture::game::tube);
            left->setScaleX(segmentSize / left->getContentSize().width);
            right = RectangleBody::createWithSpriteFrameName(texture::game::tube);
            right->setScaleX(segmentSize / right->getContentSize().width);
        }

        left->setRotation(-90);
        left->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_RIGHT);
        left->setPosition({0.F, top - i * segmentSize});
        addChild(left);
        mPhysics->registerObstacle(left);

        right->setRotation(-90);
        right->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_RIGHT);
        right->setPosition({getContentSize().width, top - i * segmentSize});
        addChild(right);
        mPhysics->registerObstacle(right);
    }
}

float ar::Frame::getBorder() const {
    return mBorder;
}

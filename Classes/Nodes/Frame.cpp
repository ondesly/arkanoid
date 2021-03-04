//
//  Frame.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 04.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include "Physics/Body.h"
#include "Physics/Physics.h"

#include "Frame.h"

namespace {

    const char *cEmptyFrame = "empty";
    const char *cTubeFrame = "tube";
    const char *cTubeDecorFrame = "tube_decor";
    const char *cTubeCornerLeftFrame = "tube_corner_left";
    const char *cTubeCornerRightFrame = "tube_corner_right";

}

ar::Frame *ar::Frame::create(const std::shared_ptr<Physics> &physics) {
    auto frame = new(std::nothrow) Frame(physics);
    if (frame && frame->init()) {
        frame->autorelease();
        return frame;
    }
    CC_SAFE_DELETE(frame);
    return nullptr;
}

ar::Frame::Frame(const std::shared_ptr<Physics> &physics) : mPhysics(physics) {

}

void ar::Frame::setHeaderSize(float size) {
    mHeaderSize = size;
}

void ar::Frame::layout() {
    addHeader();
    addTop();
    addSides();
}

void ar::Frame::addHeader() {
    auto header = cocos2d::Sprite::createWithSpriteFrameName(cEmptyFrame);
    header->setColor(cocos2d::Color3B::BLACK);
    header->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
    header->setPosition({getContentSize().width / 2, getContentSize().height});
    header->setScale(getContentSize().width / header->getContentSize().width,
            mHeaderSize / header->getContentSize().height);
    addChild(header);
}

void ar::Frame::addTop() {
    auto cornerFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(cTubeCornerLeftFrame);
    auto decorFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(cTubeDecorFrame);

    const auto cornerWidth = cornerFrame->getOriginalSize().width;
    const auto segmentSize = (getContentSize().width - cornerWidth * 2 - decorFrame->getOriginalSize().width * 2) / 4;

    // Corners

    auto cornerLeft = RectangleBody::createWithSpriteFrameName(cTubeCornerLeftFrame);
    cornerLeft->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    cornerLeft->setPosition({0.F, getContentSize().height - mHeaderSize});
    addChild(cornerLeft);
    mPhysics->registerObstacle(cornerLeft);

    auto cornerRight = RectangleBody::createWithSpriteFrameName(cTubeCornerRightFrame);
    cornerRight->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_RIGHT);
    cornerRight->setPosition({getContentSize().width, getContentSize().height - mHeaderSize});
    addChild(cornerRight);
    mPhysics->registerObstacle(cornerRight);

    // Tube H

    auto tubeHLeft = RectangleBody::createWithSpriteFrameName(cTubeFrame);
    tubeHLeft->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    tubeHLeft->setPosition({cornerWidth, getContentSize().height - mHeaderSize});
    tubeHLeft->setScaleX(segmentSize / tubeHLeft->getContentSize().width);
    addChild(tubeHLeft);
    mPhysics->registerObstacle(tubeHLeft);

    auto tubeHCenter = RectangleBody::createWithSpriteFrameName(cTubeFrame);
    tubeHCenter->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
    tubeHCenter->setPosition({getContentSize().width / 2, getContentSize().height - mHeaderSize});
    tubeHCenter->setScaleX(segmentSize * 2 / tubeHCenter->getContentSize().width);
    addChild(tubeHCenter);
    mPhysics->registerObstacle(tubeHCenter);

    auto tubeHRight = RectangleBody::createWithSpriteFrameName(cTubeFrame);
    tubeHRight->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_RIGHT);
    tubeHRight->setPosition({getContentSize().width - cornerWidth, getContentSize().height - mHeaderSize});
    tubeHRight->setScaleX(segmentSize / tubeHRight->getContentSize().width);
    addChild(tubeHRight);
    mPhysics->registerObstacle(tubeHRight);

    // Decor

    auto decorLeft = RectangleBody::createWithSpriteFrameName(cTubeDecorFrame);
    decorLeft->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    decorLeft->setPosition({cornerWidth + segmentSize, getContentSize().height - mHeaderSize});
    addChild(decorLeft);
    mPhysics->registerObstacle(decorLeft);

    auto decorRight = RectangleBody::createWithSpriteFrameName(cTubeDecorFrame);
    decorRight->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_RIGHT);
    decorRight->setPosition({getContentSize().width - segmentSize - cornerWidth, getContentSize().height - mHeaderSize});
    addChild(decorRight);
    mPhysics->registerObstacle(decorRight);
}

void ar::Frame::addSides() {
    auto cornerFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(cTubeCornerLeftFrame);
    auto decorFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(cTubeDecorFrame);

    const auto top = getContentSize().height - mHeaderSize - cornerFrame->getOriginalSize().height;
    const auto segmentSize = decorFrame->getOriginalSize().width;
    const auto segmentsCount = size_t(std::ceil(top / segmentSize));

    for (size_t i = 0; i < segmentsCount; ++i) {
        RectangleBody *left;
        RectangleBody *right;

        if (i % 2 == 0) {
            left = RectangleBody::createWithSpriteFrameName(cTubeDecorFrame);
            right = RectangleBody::createWithSpriteFrameName(cTubeDecorFrame);
        } else {
            left = RectangleBody::createWithSpriteFrameName(cTubeFrame);
            left->setScaleX(segmentSize / left->getContentSize().width);
            right = RectangleBody::createWithSpriteFrameName(cTubeFrame);
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

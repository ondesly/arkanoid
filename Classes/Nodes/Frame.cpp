//
//  Frame.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 04.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include "Frame.h"

ar::Frame *ar::Frame::create() {
    auto frame = new(std::nothrow) Frame();
    if (frame && frame->init()) {
        frame->autorelease();
        return frame;
    }
    CC_SAFE_DELETE(frame);
    return nullptr;
}

void ar::Frame::setHeaderSize(float size) {
    mHeaderSize = size;
}

void ar::Frame::layout() {

    // Header

    auto header = cocos2d::Sprite::createWithSpriteFrameName("empty");
    header->setColor(cocos2d::Color3B::BLACK);
    header->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
    header->setPosition({getContentSize().width / 2, getContentSize().height});
    header->setScale(getContentSize().width / header->getContentSize().width,
            mHeaderSize / header->getContentSize().height);
    addChild(header);

    //

    auto cornerFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("tube_corner_left");
    auto decorFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("tube_decor");

    const auto cornerSize = cornerFrame->getOriginalSize();
    const auto hSegmentSize = (getContentSize().width - cornerSize.width * 2 - decorFrame->getOriginalSize().width * 2) / 4;

    // Corners

    auto cornerLeft = cocos2d::Sprite::createWithSpriteFrameName("tube_corner_left");
    cornerLeft->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    cornerLeft->setPosition({0.F, getContentSize().height - mHeaderSize});
    addChild(cornerLeft);

    auto cornerRight = cocos2d::Sprite::createWithSpriteFrameName("tube_corner_right");
    cornerRight->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_RIGHT);
    cornerRight->setPosition({getContentSize().width, getContentSize().height - mHeaderSize});
    addChild(cornerRight);

    // Tube H

    auto tubeHLeft = cocos2d::Sprite::createWithSpriteFrameName("tube");
    tubeHLeft->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    tubeHLeft->setPosition({cornerSize.width, getContentSize().height - mHeaderSize});
    tubeHLeft->setScaleX(hSegmentSize / tubeHLeft->getContentSize().width);
    addChild(tubeHLeft);

    auto tubeHCenter = cocos2d::Sprite::createWithSpriteFrameName("tube");
    tubeHCenter->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
    tubeHCenter->setPosition({getContentSize().width / 2, getContentSize().height - mHeaderSize});
    tubeHCenter->setScaleX(hSegmentSize * 2 / tubeHCenter->getContentSize().width);
    addChild(tubeHCenter);

    auto tubeHRight = cocos2d::Sprite::createWithSpriteFrameName("tube");
    tubeHRight->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_RIGHT);
    tubeHRight->setPosition({getContentSize().width - cornerSize.width, getContentSize().height - mHeaderSize});
    tubeHRight->setScaleX(hSegmentSize / tubeHRight->getContentSize().width);
    addChild(tubeHRight);

    // Decor

    auto decorLeft = cocos2d::Sprite::createWithSpriteFrameName("tube_decor");
    decorLeft->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    decorLeft->setPosition({cornerSize.width + hSegmentSize, getContentSize().height - mHeaderSize});
    addChild(decorLeft);

    auto decorRight = cocos2d::Sprite::createWithSpriteFrameName("tube_decor");
    decorRight->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_RIGHT);
    decorRight->setPosition({getContentSize().width - hSegmentSize - cornerSize.width, getContentSize().height - mHeaderSize});
    addChild(decorRight);

    // Sides

    const auto vSegmentSize = decorFrame->getOriginalSize().width;
    const auto sideTop = getContentSize().height - mHeaderSize - cornerSize.height;
    const auto vSegmentsCount = size_t(std::ceil(sideTop / vSegmentSize));

    for (size_t i = 0; i < vSegmentsCount; ++i) {
        cocos2d::Sprite *leftSide;
        cocos2d::Sprite *rightSide;

        if (i % 2 == 0) {
            leftSide = cocos2d::Sprite::createWithSpriteFrameName("tube_decor");
            rightSide = cocos2d::Sprite::createWithSpriteFrameName("tube_decor");
        } else {
            leftSide = cocos2d::Sprite::createWithSpriteFrameName("tube");
            leftSide->setScaleX(vSegmentSize / leftSide->getContentSize().width);
            rightSide = cocos2d::Sprite::createWithSpriteFrameName("tube");
            rightSide->setScaleX(vSegmentSize / rightSide->getContentSize().width);
        }

        leftSide->setRotation(-90);
        leftSide->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_RIGHT);
        leftSide->setPosition({0.F, sideTop - i * vSegmentSize});
        addChild(leftSide);

        rightSide->setRotation(-90);
        rightSide->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_RIGHT);
        rightSide->setPosition({getContentSize().width, sideTop - i * vSegmentSize});
        addChild(rightSide);
    }
}
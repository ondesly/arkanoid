//
//  GameScene.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <random>

#include <base/CCEventListenerTouch.h>

#include "Nodes/Frame.h"
#include "Objects/Block.h"
#include "Objects/Platform.h"
#include "Physics/CircleBody.h"
#include "Physics/Physics.h"

#include "GameScene.h"

namespace {

    namespace spriteFrame {

        const char *bg = "bg";
        const char *ball = "ball";
        const char *platform = "platform";
        const char *platformShadow = "platform_shadow";
        const char *empty = "empty";
        const char *tube = "tube";

    }

    const size_t cPhysicsTicksPerFrame = 10;

    const float cPlatformSpeed = 0.4F;
    const float cPlatformFriction = 0.5F;

    const int cShadowOpacity = 100;

}

ar::GameScene *ar::GameScene::create() {
    auto scene = new(std::nothrow) GameScene();
    if (scene && scene->init()) {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

bool ar::GameScene::init() {
    if (!cocos2d::Scene::init()) {
        return false;
    }

    //

    mPhysics = std::make_shared<Physics>(cPhysicsTicksPerFrame);

    //

    addBackground();

    //

    const auto headerSize = getContentSize().width / 10.F;
    const auto tubeSize = cocos2d::SpriteFrameCache::getInstance()->
            getSpriteFrameByName(spriteFrame::tube)->getOriginalSize().height;

    addFrameShadow({tubeSize, tubeSize + headerSize});

    //

    std::default_random_engine gen{std::random_device{}()};
    std::uniform_int_distribution<size_t> distrib{0, 2};

    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            auto block = Block::create(distrib(gen));
            block->setTextureRect(cocos2d::Rect(cocos2d::Vec2::ZERO, {50.F, 30.F}));
            block->setPosition({
                    140.F + i * (block->getContentSize().width + 2.F),
                    getContentSize().height - 150.F - j * (block->getContentSize().height + 2.F)});
            addChild(block);

            mPhysics->registerObstacle(block);
        }
    }

    //

    mPlatform = makePlatform();
    mPlatform->setPosition(getContentSize() / 2);
    addChild(mPlatform);

    mBall = makeBall();
    mBall->setPosition({
            mPlatform->getPosition().x,
            mPlatform->getPosition().y + mPlatform->getContentSize().height / 2 + mBall->getContentSize().height / 2});
    addChild(mBall);

    //

    addFrame(mPhysics, headerSize);

    //

    enableTouch();

    //

    return true;
}

bool ar::GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent) {
    const auto location = touch->getLocation();
    mPlatform->setTargetX(location.x);

    if (mBall->getVelocity().equals({})) {
        const cocos2d::Vec2 vel{location.x < mPlatform->getPosition().x ? -1.F : 1.F, 1.F};
        mBall->setVelocity(vel.getNormalized());
    }

    return true;
}

void ar::GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent) {
    const auto location = touch->getLocation();
    mPlatform->setTargetX(location.x);
}

void ar::GameScene::enableTouch() {
    mTouchListener = cocos2d::EventListenerTouchOneByOne::create();
    mTouchListener->onTouchBegan = std::bind(&GameScene::onTouchBegan, this, std::placeholders::_1, std::placeholders::_2);
    mTouchListener->onTouchMoved = std::bind(&GameScene::onTouchMoved, this, std::placeholders::_1, std::placeholders::_2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mTouchListener, this);
}

void ar::GameScene::addBackground() {
    auto bg = cocos2d::Sprite::createWithSpriteFrameName(spriteFrame::bg);
    bg->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    bg->setTextureRect(cocos2d::Rect({}, getContentSize()));
    addChild(bg);

    bg->getTexture()->setTexParameters({GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT});
}

void ar::GameScene::addFrame(const std::shared_ptr<Physics> &physics, float headerSize) {
    auto frame = Frame::create(physics);
    frame->setHeaderSize(headerSize);
    frame->setContentSize(getContentSize());
    addChild(frame);

    frame->layout();
}

void ar::GameScene::addFrameShadow(const cocos2d::Vec2 &offset) {
    auto leftShadow = cocos2d::Sprite::createWithSpriteFrameName(spriteFrame::empty);
    leftShadow->setColor(cocos2d::Color3B::BLACK);
    leftShadow->setOpacity(cShadowOpacity);
    leftShadow->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    leftShadow->setPosition({offset.x, 0.F});
    leftShadow->setScale(offset.x / leftShadow->getContentSize().width,
            (getContentSize().height - offset.y) / leftShadow->getContentSize().height);
    addChild(leftShadow);

    auto topShadow = cocos2d::Sprite::createWithSpriteFrameName(spriteFrame::empty);
    topShadow->setColor(cocos2d::Color3B::BLACK);
    topShadow->setOpacity(cShadowOpacity);
    topShadow->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    topShadow->setPosition({offset.x * 2, getContentSize().height - offset.y});
    topShadow->setScale((getContentSize().width - offset.x) / leftShadow->getContentSize().width,
            offset.x / leftShadow->getContentSize().height);
    addChild(topShadow);
}

ar::Platform *ar::GameScene::makePlatform() {
    auto platform = Platform::createWithSpriteFrameName(spriteFrame::platform);

    auto shadow = cocos2d::Sprite::createWithSpriteFrameName(spriteFrame::platformShadow);
    shadow->setPosition({platform->getContentSize().width / 2 + platform->getContentSize().height / 2, 0.F});
    platform->addChild(shadow, -1);

    //

    mPhysics->registerAgent(platform);
    mPhysics->registerObstacle(platform);

    platform->setSpeed(cPlatformSpeed);
    platform->setFriction(cPlatformFriction);

    return platform;
}

ar::Body *ar::GameScene::makeBall() {
    auto ball = CircleBody::createWithSpriteFrameName(spriteFrame::ball);

    mPhysics->registerAgent(ball);

    ball->setSpeed(mBallSpeed);

    return ball;
}
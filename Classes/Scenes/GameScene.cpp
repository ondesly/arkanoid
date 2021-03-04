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
#include "Physics/Body.h"
#include "Physics/Physics.h"

#include "GameScene.h"

namespace {

    namespace spriteFrame {

        const char *bg = "bg";
        const char *ball = "ball";

    }

    const size_t cPhysicsTicksPerFrame = 10;

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

    addBackground();

    //

    mPhysics = std::make_shared<Physics>(cPhysicsTicksPerFrame);

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

    mPlatform = Platform::create();
    mPlatform->setTextureRect(cocos2d::Rect(cocos2d::Vec2::ZERO, {100.F, 20.F}));
    mPlatform->setPosition(getContentSize() / 2);
    addChild(mPlatform);

    mPlatform->setSpeed(0.4F);
    mPlatform->setFriction(0.5F);

    mPhysics->registerAgent(mPlatform);
    mPhysics->registerObstacle(mPlatform);

    //

    mBall = CircleBody::createWithSpriteFrameName(spriteFrame::ball);
    mBall->setPosition({mPlatform->getPosition().x, mPlatform->getPosition().y + mPlatform->getContentSize().height / 2 + mBall->getContentSize().height / 2});
    addChild(mBall);

    mBall->setSpeed(0.5F);

    mPhysics->registerAgent(mBall);

    //

    addFrame(mPhysics);

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

void ar::GameScene::enableTouch() {
    mTouchListener = cocos2d::EventListenerTouchOneByOne::create();
    mTouchListener->onTouchBegan = std::bind(&GameScene::onTouchBegan, this, std::placeholders::_1, std::placeholders::_2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mTouchListener, this);
}

void ar::GameScene::addBackground() {
    auto bg = cocos2d::Sprite::createWithSpriteFrameName(spriteFrame::bg);
    bg->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    bg->setTextureRect(cocos2d::Rect({}, getContentSize()));
    addChild(bg);

    bg->getTexture()->setTexParameters({GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT});
}

void ar::GameScene::addFrame(const std::shared_ptr<Physics> &physics) {
    auto frame = Frame::create(physics);
    frame->setHeaderSize(getContentSize().width / 10.F);
    frame->setContentSize(getContentSize());
    addChild(frame);

    frame->layout();
}
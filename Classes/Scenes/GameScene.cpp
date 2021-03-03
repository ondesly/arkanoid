//
//  GameScene.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <random>

#include <base/CCEventListenerTouch.h>

#include "Objects/Platform.h"
#include "Physics/Body.h"
#include "Physics/Physics.h"

#include "GameScene.h"

namespace {

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

    mPhysics = std::make_unique<Physics>(cPhysicsTicksPerFrame);

    //

    auto left = RectangleBody::create();
    left->setTextureRect(cocos2d::Rect(cocos2d::Vec2::ZERO, {10.F, getContentSize().height}));
    left->setPosition({100.F, getContentSize().height / 2});
    addChild(left);

    mPhysics->registerObstacle(left);

    auto right = RectangleBody::create();
    right->setTextureRect(cocos2d::Rect(cocos2d::Vec2::ZERO, {10.F, getContentSize().height}));
    right->setPosition({getContentSize().width - 100.F, getContentSize().height / 2});
    addChild(right);

    mPhysics->registerObstacle(right);

    auto top = RectangleBody::create();
    top->setTextureRect(cocos2d::Rect(cocos2d::Vec2::ZERO, {getContentSize().width, 10.F}));
    top->setPosition({getContentSize().width / 2, getContentSize().height - 100.F});
    addChild(top);

    mPhysics->registerObstacle(top);

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

    mBall = CircleBody::create();
    mBall->setTextureRect(cocos2d::Rect(cocos2d::Vec2::ZERO, {10.F, 10.F}));
    mBall->setPosition({getContentSize().width / 2 - 200.F, getContentSize().height / 4 * 3});
    addChild(mBall);

    mPhysics->registerAgent(mBall);

    mBall->setSpeed(0.5F);

    std::default_random_engine gen{std::random_device{}()};
    std::uniform_real_distribution<float> distrib{-1.F, 1.F};

    mBall->setVelocity({distrib(gen), distrib(gen)});

    //

    enableTouch();

    //

    return true;
}

bool ar::GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent) {
    const auto location = touch->getLocation();
    mPlatform->setTargetX(location.x);

    return true;
}

void ar::GameScene::enableTouch() {
    mTouchListener = cocos2d::EventListenerTouchOneByOne::create();
    mTouchListener->onTouchBegan = std::bind(&GameScene::onTouchBegan, this, std::placeholders::_1, std::placeholders::_2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mTouchListener, this);
}

//
//  GameScene.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <random>

#include <base/CCEventListenerTouch.h>

#include "Physics/Agent.h"
#include "Physics/Body.h"
#include "Physics/Physics.h"

#include "GameScene.h"

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

    mPhysics = std::make_unique<Physics>();

    //

    auto left = Body::create();
    left->setTextureRect(cocos2d::Rect(cocos2d::Vec2::ZERO, {10.F, getContentSize().height}));
    left->setPosition({100.F, (getContentSize().height - left->getContentSize().height) / 2});
    addChild(left);

    mPhysics->registerObstacle(left);

    auto right = Body::create();
    right->setTextureRect(cocos2d::Rect(cocos2d::Vec2::ZERO, {10.F, getContentSize().height}));
    right->setPosition({getContentSize().width - 100.F, (getContentSize().height - right->getContentSize().height) / 2});
    addChild(right);

    mPhysics->registerObstacle(right);

    const auto screen_diff = (getContentSize().height - getContentSize().width) / 2;

    auto bottom = Body::create();
    bottom->setTextureRect(cocos2d::Rect(cocos2d::Vec2::ZERO, {getContentSize().width, 10.F}));
    bottom->setPosition({(getContentSize().width - bottom->getContentSize().width) / 2, screen_diff + 100.F});
    addChild(bottom);

    mPhysics->registerObstacle(bottom);

    auto top = Body::create();
    top->setTextureRect(cocos2d::Rect(cocos2d::Vec2::ZERO, {getContentSize().width, 10.F}));
    top->setPosition({(getContentSize().width - bottom->getContentSize().width), getContentSize().height - screen_diff - 100.F});
    addChild(top);

    mPhysics->registerObstacle(top);

    //

    mBall = Body::create();
    mBall->setTextureRect(cocos2d::Rect(cocos2d::Vec2::ZERO, {10.F, 10.F}));
    mBall->setPosition(getContentSize() / 2);
    addChild(mBall);

    mPhysics->registerAgent(mBall);

    //

    enableTouch();

    //

    return true;
}

bool ar::GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent) {
    static std::default_random_engine gen{std::random_device{}()};
    static std::uniform_int_distribution<float> distrib{-5.F, 5.F};

    mBall->setVelocity({distrib(gen), distrib(gen)});

    return true;
}

void ar::GameScene::enableTouch() {
    mTouchListener = cocos2d::EventListenerTouchOneByOne::create();
    mTouchListener->onTouchBegan = std::bind(&GameScene::onTouchBegan, this, std::placeholders::_1, std::placeholders::_2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mTouchListener, this);
}

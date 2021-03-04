//
//  GameScene.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <base/CCEventListenerTouch.h>

#include "Nodes/Blocks.h"
#include "Nodes/Frame.h"
#include "Objects/Platform.h"
#include "Physics/CircleBody.h"
#include "Physics/Physics.h"
#include "Resources.h"

#include "GameScene.h"

namespace {

    const size_t cPhysicsTicksPerFrame = 10;

    const float cPlatformSpeed = 0.4F;
    const float cPlatformFriction = 0.5F;

    const int cShadowOpacity = 100;

    const size_t cBlocksHCount = 15;
    const size_t cBlocksVCount = 5;

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
            getSpriteFrameByName(texture::game::tube)->getOriginalSize().height;

    addFrameShadow({tubeSize, tubeSize + headerSize});

    //

    mBlocks = makeBlocks(mPhysics, {tubeSize, headerSize + tubeSize * 4});
    addChild(mBlocks);

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
    auto bg = cocos2d::Sprite::createWithSpriteFrameName(texture::bg::bg);
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
    auto leftShadow = cocos2d::Sprite::createWithSpriteFrameName(texture::game::empty);
    leftShadow->setColor(cocos2d::Color3B::BLACK);
    leftShadow->setOpacity(cShadowOpacity);
    leftShadow->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    leftShadow->setPosition({offset.x, 0.F});
    leftShadow->setScale(offset.x / leftShadow->getContentSize().width,
            (getContentSize().height - offset.y) / leftShadow->getContentSize().height);
    addChild(leftShadow);

    auto topShadow = cocos2d::Sprite::createWithSpriteFrameName(texture::game::empty);
    topShadow->setColor(cocos2d::Color3B::BLACK);
    topShadow->setOpacity(cShadowOpacity);
    topShadow->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    topShadow->setPosition({offset.x * 2, getContentSize().height - offset.y});
    topShadow->setScale((getContentSize().width - offset.x) / leftShadow->getContentSize().width,
            offset.x / leftShadow->getContentSize().height);
    addChild(topShadow);
}

ar::Blocks *ar::GameScene::makeBlocks(const std::shared_ptr<Physics> &physics, const cocos2d::Vec2 &offset) {
    auto blocks = Blocks::create(physics);
    blocks->setCounts(cBlocksHCount, cBlocksVCount);
    blocks->setOffset(offset);
    blocks->setContentSize(getContentSize());

    blocks->layout();

    return blocks;
}

ar::Platform *ar::GameScene::makePlatform() {
    auto platform = Platform::createWithSpriteFrameName(texture::game::platform);

    auto shadow = cocos2d::Sprite::createWithSpriteFrameName(texture::game::platformShadow);
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
    auto ball = CircleBody::createWithSpriteFrameName(texture::game::ball);

    mPhysics->registerAgent(ball);

    ball->setSpeed(mBallSpeed);

    return ball;
}
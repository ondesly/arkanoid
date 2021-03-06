//
//  GameScene.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <base/CCEventListenerTouch.h>

#include "Nodes/Blocks.h"
#include "Nodes/Dialog.h"
#include "Nodes/Frame.h"
#include "Nodes/Header.h"
#include "Objects/Ball.h"
#include "Objects/Platform.h"
#include "Physics/Physics.h"
#include "Resources.h"

#include "GameScene.h"

namespace {

    const size_t cPhysicsTicksPerPixel = 10;

    const float cBallSpeed = 0.03F;
    const float cBallAcceleration = 1.1F;
    const size_t cDestroyedBlockCountToAccelerate = 5;

    const float cPlatformSpeed = 0.02F;
    const float cPlatformFriction = 0.5F;

    const size_t cBlocksHCount = 15;
    const size_t cBlocksVCount = 5;

    const char *cGameComplete = "GAME COMPLETE";
    const char *cGameOver = "GAME OVER";

    namespace z_order {

        int background = 0;
        int shadow = background + 1;
        int blocks = shadow + 1;
        int platform = blocks + 1;
        int ball = platform + 1;
        int frame = ball + 1;
        int header = frame + 1;
        int dialog = header + 1;

    }

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

    mPhysics = makePhysics();

    addUI();
    addListeners();

    enableTouch();

    //

    startGame();

    //

    return true;
}

void ar::GameScene::startGame() {
    mScore = 0;
    mDestroyedBlocksCount = 0;

    //

    mPlatform->setVisible(true);
    mPlatform->setVelocity({});
    mPlatform->setPosition({getContentSize().width / 2, mGameArea.size.height - mGameArea.size.width});

    mBall->setVisible(true);
    mBall->setVelocity({});
    mBall->setPosition({
            mPlatform->getPosition().x,
            mPlatform->getPosition().y + mPlatform->getContentSize().height / 2 + mBall->getContentSize().height / 2});

    //

    mBlocks->reset();

    //

    mTouchListener->setEnabled(true);
}

void ar::GameScene::endGame() {
    mBall->setVisible(false);
    mPlatform->setVisible(false);

    //

    mHeader->setScore(0);

    //

    mTouchListener->setEnabled(false);
}

std::shared_ptr<ar::Physics> ar::GameScene::makePhysics() const {
    auto ballFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(texture::game::ball);
    const auto ballWidth = ballFrame->getOriginalSize().width;

    return std::make_shared<Physics>(ballWidth * cPhysicsTicksPerPixel);
}

void ar::GameScene::addUI() {
    auto bg = makeBackground();
    addChild(bg, z_order::background);

    //

    mHeader = Header::create({getContentSize().width, getContentSize().width * 0.2F});
    mHeader->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    mHeader->setPosition({0.F, getContentSize().height});
    addChild(mHeader, z_order::header);

    //

    auto frame = Frame::create(mPhysics);
    frame->setContentSize({getContentSize().width, getContentSize().height - mHeader->getContentSize().height});
    addChild(frame, z_order::frame);

    //

    mGameArea = {
            frame->getBorder(), 0.F,
            frame->getContentSize().width - frame->getBorder() * 2, frame->getContentSize().height - frame->getBorder()};

    //

    mBlocks = Blocks::create(mPhysics);
    mBlocks->setCounts(cBlocksHCount, cBlocksVCount);
    mBlocks->setBlockSize(mGameArea.size.width / cBlocksHCount);
    mBlocks->setOffset({mGameArea.origin.x, mHeader->getContentSize().height + frame->getBorder() * 4});
    mBlocks->setContentSize(getContentSize());
    addChild(mBlocks, z_order::blocks);

    //

    auto leftShadow = makeShadow({mBlocks->getBlockSize() / 2, mGameArea.size.height});
    leftShadow->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    leftShadow->setPosition(mGameArea.origin);
    addChild(leftShadow, z_order::shadow);

    auto topShadow = makeShadow({mGameArea.size.width - mBlocks->getBlockSize() / 2, mBlocks->getBlockSize() / 2});
    topShadow->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    topShadow->setPosition({mGameArea.origin.x + mBlocks->getBlockSize() / 2, mGameArea.size.height});
    addChild(topShadow, z_order::shadow);

    //

    mPlatform = makePlatform();
    addChild(mPlatform, z_order::platform);

    mBall = makeBall();
    addChild(mBall, z_order::ball);
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

cocos2d::Sprite *ar::GameScene::makeBackground() const {
    auto bg = cocos2d::Sprite::createWithSpriteFrameName(texture::bg::bg);
    bg->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    bg->setTextureRect({{}, getContentSize()});
    bg->getTexture()->setTexParameters({GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT});

    return bg;
}

cocos2d::Sprite *ar::GameScene::makeShadow(const cocos2d::Size &size) const {
    auto shadow = cocos2d::Sprite::createWithSpriteFrameName(texture::game::empty);
    shadow->setColor(cocos2d::Color3B::BLACK);
    shadow->setOpacity(opacity::shadow);
    shadow->setScale(size.width / shadow->getContentSize().width, size.height / shadow->getContentSize().height);

    return shadow;
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

ar::Ball *ar::GameScene::makeBall() {
    auto ball = Ball::create(texture::game::ball);
    ball->setSpeed(cBallSpeed);

    mPhysics->registerAgent(ball);

    //

    return ball;
}

void ar::GameScene::addListeners() {
    auto onBlockDestroyed = cocos2d::EventListenerCustom::create(event::onBlockDestroyed, [&](cocos2d::EventCustom *event) {
        mScore += score::blockValue;

        mHeader->setScore(mScore);

        //

        mDestroyedBlocksCount += 1;

        if (mDestroyedBlocksCount % cDestroyedBlockCountToAccelerate == 0) {
            mBall->setSpeed(mBall->getSpeed() * cBallAcceleration);
        }

        if (mDestroyedBlocksCount == cBlocksHCount * cBlocksVCount) {
            endGame();
            showDialog(cGameComplete);
        }
    });
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(onBlockDestroyed, this);

    auto onBallOut = cocos2d::EventListenerCustom::create(event::onBallOut, [&](cocos2d::EventCustom *event) {
        endGame();
        showDialog(cGameOver);
    });
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(onBallOut, this);
}

void ar::GameScene::showDialog(const std::string &title) {
    auto dialog = Dialog::create(mGameArea.size, title, std::to_string(mScore), [&](Dialog *dialog) {
        dialog->removeFromParent();

        startGame();
    });
    dialog->setPosition({getContentSize().width / 2, 0.F});
    addChild(dialog, z_order::dialog);
}
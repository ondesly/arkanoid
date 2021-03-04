//
//  GameScene.h
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <memory>

#include <2d/CCScene.h>

namespace cocos2d {

    class Event;

    class EventListenerTouchOneByOne;

    class Touch;

}

namespace ar {

    class Blocks;

    class Body;

    class Physics;

    class Platform;

    class GameScene : public cocos2d::Scene {
    public:

        static GameScene *create();

    public:

        bool init() override;

    private:

        std::shared_ptr<Physics> mPhysics;

        cocos2d::EventListenerTouchOneByOne *mTouchListener;

        Blocks *mBlocks;
        Body *mBall;
        Platform *mPlatform;

        size_t mDestroyedBlocksCount = 0;

    private:

        void addBackground();

        void addFrame(const std::shared_ptr<Physics> &physics, float headerSize);

        void addFrameShadow(float size, const cocos2d::Vec2 &offset);

        void addHeader(float headerSize);

        Blocks *makeBlocks(const std::shared_ptr<Physics> &physics, float blockSize, const cocos2d::Vec2 &offset);

        Platform *makePlatform();

        Body *makeBall();

        void enableTouch();

        bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);

        void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);

        void addListeners();

    };

}
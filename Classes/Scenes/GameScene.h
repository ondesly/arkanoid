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

    class Agent;

    class Physics;

    class GameScene : public cocos2d::Scene {
    public:

        static GameScene *create();

    public:

        bool init() override;

    private:

        std::unique_ptr<Physics> mPhysics;

        cocos2d::EventListenerTouchOneByOne *mTouchListener;

        Agent *mBall;

    private:

        void enableTouch();

        bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);

    };

}
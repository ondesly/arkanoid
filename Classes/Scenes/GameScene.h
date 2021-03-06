//
//  GameScene.h
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <memory>
#include <string>

#include <2d/CCScene.h>

namespace cocos2d {

    class Event;

    class EventListenerTouchOneByOne;

    class Sprite;

    class Touch;

}

namespace ar {

    class Ball;

    class Blocks;

    class Header;

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

        Header *mHeader;
        Blocks *mBlocks;
        Ball *mBall;
        Platform *mPlatform;

        size_t mScore = 0;
        size_t mDestroyedBlocksCount = 0;

        cocos2d::Rect mGameArea;

    private:

        std::shared_ptr<Physics> makePhysics() const;

        void addUI();

        cocos2d::Sprite *makeBackground() const;

        cocos2d::Sprite *makeShadow(const cocos2d::Size &size) const;

        Platform *makePlatform();

        Ball *makeBall();

        void enableTouch();

        bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);

        void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);

        void addListeners();

        void showDialog(const std::string &title);

        void startGame();

        void endGame();


    };

}
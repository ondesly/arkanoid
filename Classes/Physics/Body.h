//
//  Body.h
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <2d/CCSprite.h>

namespace ar {

    class Body : public cocos2d::Sprite {
    public:

        bool init() override;

        virtual cocos2d::Vec2 getCollisionResult(Body *obstacle) const = 0;

        const cocos2d::Vec2 &getVelocity() const;

        void setVelocity(const cocos2d::Vec2 &velocity);

        float getFriction() const;

        void setFriction(float value);

    private:

        cocos2d::Vec2 mVelocity;
        float mFriction = 0.F;

    };

    class RectangleBody : public Body {
    public:

        static RectangleBody *create();

    public:

        cocos2d::Vec2 getCollisionResult(Body *obstacle) const override;

    };

    class CircleBody : public Body {
    public:

        static CircleBody *create();

    public:

        cocos2d::Vec2 getCollisionResult(Body *obstacle) const override;

    };

}
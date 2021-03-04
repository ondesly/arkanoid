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

        virtual bool isCollided(Body *obstacle) const = 0;

        virtual cocos2d::Vec2 getVelocityAfterCollision(Body *obstacle) const = 0;

        virtual void onCollision();

    public:

        cocos2d::Rect getVisibleRect() const;

        void updatePosition();

        void updateVelocityAfterCollision(Body *obstacle);

        float getSpeed() const;

        void setSpeed(float speed);

        const cocos2d::Vec2 &getVelocity() const;

        void setVelocity(const cocos2d::Vec2 &velocity);

        float getFriction() const;

        void setFriction(float value);

    protected:

        float mSpeed = 0.F;
        cocos2d::Vec2 mVelocity;
        float mFriction = 0.F;

    };

}
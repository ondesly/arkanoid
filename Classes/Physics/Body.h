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

        const cocos2d::Vec2 &getVelocity() const;

        void setVelocity(const cocos2d::Vec2 &velocity);

    private:

        cocos2d::Vec2 mVelocity;

    };

    class RectangleBody : public Body {
    public:

        static RectangleBody *create();

    };

    class CircleBody : public Body {
    public:

        static CircleBody *create();

    };

}
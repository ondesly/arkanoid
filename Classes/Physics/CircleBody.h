//
//  CircleBody.h
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 04.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <string>

#include "Physics/Body.h"

namespace ar {

    class CircleBody : public Body {
    public:

        static CircleBody *create();

        static CircleBody *createWithSpriteFrameName(const std::string &name);

    public:

        bool isCollided(Body *obstacle) override;

        cocos2d::Vec2 getVelocityAfterCollision(Body *obstacle) override;

    };

}
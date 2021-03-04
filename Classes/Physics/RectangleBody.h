//
//  RectangleBody.h
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 04.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <string>

#include "Physics/Body.h"

namespace ar {

    class RectangleBody : public Body {
    public:

        static RectangleBody *create();

        static RectangleBody *createWithSpriteFrameName(const std::string &name);

    public:

        bool isCollided(Body *obstacle) const override;

        cocos2d::Vec2 getVelocityAfterCollision(Body *obstacle) const override;

    };

}


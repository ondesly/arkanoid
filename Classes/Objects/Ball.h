//
//  Ball.h
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 04.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include "Physics/CircleBody.h"

namespace ar {

    class Ball : public CircleBody {
    public:

        static Ball *create(const std::string &name);

    public:

        void setPosition(const cocos2d::Vec2 &pos) override;

    };

}
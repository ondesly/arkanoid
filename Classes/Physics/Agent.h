//
//  Agent.h
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include "Physics/Body.h"

namespace ar {

    class Agent : public Body {
    public:

        static Agent *create();

    public:

        bool init() override;

        float getRadius() const;

        const cocos2d::Vec2 &getVelocity() const;

        void setVelocity(const cocos2d::Vec2 &velocity);

    private:

        cocos2d::Vec2 mVelocity;

    };

}
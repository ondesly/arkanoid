//
//  Platform.h
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include "Physics/Body.h"

namespace ar {

    class Platform : public RectangleBody {
    public:

        static Platform *createWithSpriteFrameName(const std::string &name);

    public:

        void setPosition(const cocos2d::Vec2 &pos) override;

        void setTargetX(float x);

    private:

        float mTargetX = 0.F;

    };

}
//
//  Block.h
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 03.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include "Physics/RectangleBody.h"

namespace coco2d {

    class Color3B;

}

namespace ar {

    class Block : public RectangleBody {
    public:

        static Block *createWithSpriteFrameName(const std::string &name, int type);

    public:

        bool initWithSpriteFrameName(const std::string &name, int type);

        void onCollision() override;

        void setType(int type);

    private:

        int mType = 0;

    private:

        const cocos2d::Color3B &getColor(int type) const;

    };

}
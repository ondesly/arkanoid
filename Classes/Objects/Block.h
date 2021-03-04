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

        static Block *createWithSpriteFrameName(const std::string &name, size_t type);

    public:

        bool initWithSpriteFrameName(const std::string &name, size_t type);

        void onCollision() override;

    private:

        size_t mType = 0;

    private:

        void setType(size_t type);

        const cocos2d::Color3B &getColor(size_t type) const;

    };

}
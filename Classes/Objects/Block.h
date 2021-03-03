//
//  Block.h
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 03.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include "Physics/Body.h"

namespace ar {

    class Block : public RectangleBody {
    public:

        static Block *create(size_t type);

    public:

        bool init(size_t type);

        void onCollision() override;

    private:

        size_t mType = 0;

    private:

        void setType(size_t type);

    };

}
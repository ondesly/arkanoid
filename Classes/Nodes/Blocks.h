//
//  Blocks.h
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 04.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <memory>

#include <2d/CCSpriteBatchNode.h>

namespace ar {

    class Physics;

    class Blocks : public cocos2d::SpriteBatchNode {
    public:

        static Blocks *create(const std::shared_ptr<Physics> &physics);

    public:

        void setCounts(size_t h, size_t v);

        void setOffset(const cocos2d::Vec2 &offset);

        void layout();

    private:

        size_t mHCount;
        size_t mVCount;
        cocos2d::Vec2 mOffset;

        std::shared_ptr<Physics> mPhysics;

    private:

        Blocks(const std::shared_ptr<Physics> &physics);

    };

}
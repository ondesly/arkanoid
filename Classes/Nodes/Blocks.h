//
//  Blocks.h
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 04.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <memory>
#include <vector>

#include <2d/CCSpriteBatchNode.h>

namespace ar {

    class Block;

    class Physics;

    class Blocks : public cocos2d::SpriteBatchNode {
    public:

        static Blocks *create(const std::shared_ptr<Physics> &physics);

    public:

        void setCounts(size_t h, size_t v);

        void setOffset(const cocos2d::Vec2 &offset);

        void setBlocksSize(float blockSize);

        void layout();

        void reset();

    private:

        size_t mHCount = 0;
        size_t mVCount = 0;
        cocos2d::Vec2 mOffset;
        float mBlockSize = 0;

        std::shared_ptr<Physics> mPhysics;

        std::vector<Block *> mBlocks;

    private:

        Blocks(const std::shared_ptr<Physics> &physics);

    };

}
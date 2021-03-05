//
//  Blocks.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 04.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <random>

#include "Objects/Block.h"
#include "Physics/Physics.h"
#include "Resources.h"

#include "Blocks.h"

ar::Blocks *ar::Blocks::create(const std::shared_ptr<Physics> &physics) {
    auto blockFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(texture::game::block);

    auto blocks = new(std::nothrow) Blocks(physics);
    if (blocks && blocks->initWithTexture(blockFrame->getTexture())) {
        blocks->autorelease();
        return blocks;
    }
    CC_SAFE_DELETE(blocks);
    return nullptr;
}

ar::Blocks::Blocks(const std::shared_ptr<Physics> &physics) : mPhysics(physics) {

}

void ar::Blocks::setCounts(size_t h, size_t v) {
    mHCount = h;
    mVCount = v;
}

void ar::Blocks::setOffset(const cocos2d::Vec2 &offset) {
    mOffset = offset;
}

float ar::Blocks::getBlockSize() const {
    return mBlockSize;
}

void ar::Blocks::setBlockSize(float blockSize) {
    mBlockSize = blockSize;
}

void ar::Blocks::layout() {
    for (size_t i = 0; i < mHCount; ++i) {
        for (size_t j = 0; j < mVCount; ++j) {
            auto block = Block::createWithSpriteFrameName(texture::game::block, 0);
            block->setPosition({
                    mOffset.x + (i + 0.5F) * mBlockSize,
                    getContentSize().height - mOffset.y - (j + 0.5F) * (block->getContentSize().height)});
            block->setScaleX(mBlockSize / block->getContentSize().width);
            addChild(block);

            mBlocks.push_back(block);
            mPhysics->registerObstacle(block);
        }
    }
}

void ar::Blocks::reset() {
    static std::default_random_engine gen{std::random_device{}()};
    static std::uniform_int_distribution<int> distrib{0, 2};

    for (auto block : mBlocks) {
        block->setType(distrib(gen));
    }
}

void ar::Blocks::setContentSize(const cocos2d::Size &contentSize) {
    Node::setContentSize(contentSize);

    layout();
}

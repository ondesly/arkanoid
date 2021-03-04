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

void ar::Blocks::layout() {
    static std::default_random_engine gen{std::random_device{}()};
    static std::uniform_int_distribution<size_t> distrib{0, 2};

    const auto size = (getContentSize().width - mOffset.x * 2) / mHCount;

    for (size_t i = 0; i < mHCount; ++i) {
        for (size_t j = 0; j < mVCount; ++j) {
            auto block = Block::createWithSpriteFrameName(texture::game::block, distrib(gen));
            block->setPosition({
                    mOffset.x + (i + 0.5F) * size,
                    getContentSize().height - mOffset.y - (j + 0.5F) * (block->getContentSize().height)});
            block->setScaleX(size / block->getContentSize().width);
            addChild(block);

            mPhysics->registerObstacle(block);
        }
    }
}
//
//  Frame.h
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

    class Frame : public cocos2d::SpriteBatchNode {
    public:

        static Frame *create(const std::shared_ptr<Physics> &physics);

    public:

        void setContentSize(const cocos2d::Size &contentSize) override;

        void layout();

    private:

        std::shared_ptr<Physics> mPhysics;

    private:

        Frame(const std::shared_ptr<Physics> &physics);

    private:

        void addTop();

        void addSides();

    };

}
//
//  Frame.h
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 04.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <memory>

#include <2d/CCNode.h>

namespace ar {

    class Physics;

    class Frame : public cocos2d::Node {
    public:

        static Frame *create(const std::shared_ptr<Physics> &physics);

    public:

        void setHeaderSize(float size);

        void layout();

    private:

        float mHeaderSize = 0;

        std::shared_ptr<Physics> mPhysics;

    private:

        Frame(const std::shared_ptr<Physics> &physics);

    private:

        void addHeader();

        void addTop();

        void addSides();

    };

}
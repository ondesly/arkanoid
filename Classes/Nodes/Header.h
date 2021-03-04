//
//  Header.h
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 04.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <2d/CCNode.h>

namespace cocos2d {

    class Label;

}

namespace ar {

    class Header : public cocos2d::Node {
    public:

        static Header *create(const cocos2d::Size &size);

    public:

        bool init(const cocos2d::Size &size);

        void setScore(size_t score);

    private:

        cocos2d::Label *mScoreValue;

    };

}
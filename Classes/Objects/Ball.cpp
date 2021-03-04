//
//  Ball.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 04.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include "Ball.h"

ar::Ball *ar::Ball::create(const std::string &name) {
    auto ball = new(std::nothrow) Ball();
    if (ball && ball->initWithSpriteFrameName(name)) {
        ball->autorelease();
        return ball;
    }
    CC_SAFE_DELETE(ball);
    return nullptr;
}
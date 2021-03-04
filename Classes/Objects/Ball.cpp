//
//  Ball.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 04.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <base/CCEventDispatcher.h>

#include "Resources.h"

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

void ar::Ball::setPosition(const cocos2d::Vec2 &pos) {
    Sprite::setPosition(pos);

    if (pos.y < 0 && isVisible()) {
        setVisible(false);
        getEventDispatcher()->dispatchCustomEvent(event::onBallOut);
    }
}

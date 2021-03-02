//
//  Agent.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include "Agent.h"

ar::Agent *ar::Agent::create() {
    auto agent = new(std::nothrow) Agent();
    if (agent && agent->init()) {
        agent->autorelease();
        return agent;
    }
    CC_SAFE_DELETE(agent);
    return nullptr;
}

bool ar::Agent::init() {
    if (!Body::init()) {
        return false;
    }

    setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);

    return true;
}

float ar::Agent::getRadius() const {
    return getContentSize().width / 2;
}

const cocos2d::Vec2 &ar::Agent::getVelocity() const {
    return mVelocity;
}

void ar::Agent::setVelocity(const cocos2d::Vec2 &velocity) {
    mVelocity = velocity;
}
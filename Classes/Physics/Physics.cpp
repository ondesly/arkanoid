//
//  Physics.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <cmath>

#include <base/CCDirector.h>
#include <base/CCScheduler.h>

#include "Physics/Agent.h"
#include "Physics/Body.h"

#include "Physics.h"

ar::Physics::Physics() {
    cocos2d::Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
}

ar::Physics::~Physics() {
    cocos2d::Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
}

void ar::Physics::update(float delta) {
    if (!mAgent) {
        return;
    }

    updateAgent();
    checkCollisions();
}

void ar::Physics::updateAgent() {
    const auto &pos = mAgent->getPosition();
    const auto &velocity = mAgent->getVelocity();
    mAgent->setPosition(pos + velocity);
}

void ar::Physics::checkCollisions() {
    for (const auto &body : mObstacles) {
        const auto result = getCollisionResult(mAgent, body);

        if (!result.equals(cocos2d::Vec2::ZERO)) {
            const auto &velocity = mAgent->getVelocity();
            mAgent->setVelocity({velocity.x * result.x, velocity.y * result.y});
        }
    }
}

cocos2d::Vec2 ar::Physics::getCollisionResult(ar::Agent *agent, ar::Body *body) const {
    const auto &agentPos = agent->getPosition();
    const auto &bodyPos = body->getPosition();
    const auto &bodySize = body->getContentSize();

    cocos2d::Vec2 nearest = agentPos;
    cocos2d::Vec2 result{1.F, 1.F};

    // Horizontal

    if (agentPos.x < bodyPos.x) {
        nearest.x = bodyPos.x;
        result.x = -1.F;
    } else if (agentPos.x > bodyPos.x + bodySize.width) {
        nearest.x = bodyPos.x + bodySize.width;
        result.x = -1.F;
    }

    // Vertical

    if (agentPos.y < bodyPos.y) {
        nearest.y = bodyPos.y;
        result.y = -1.F;
    } else if (agentPos.y > bodyPos.y + bodySize.height) {
        nearest.y = bodyPos.y + bodySize.height;
        result.y = -1.F;
    }

    // Distance

    const cocos2d::Vec2 diff = agentPos - nearest;
    const float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

    if (distance <= agent->getRadius()) {
        return result;
    } else {
        return {};
    }
}

void ar::Physics::registerAgent(ar::Agent *agent) {
    mAgent = agent;
}

void ar::Physics::registerObstacles(ar::Body *obstacle) {
    mObstacles.push_back(obstacle);
}

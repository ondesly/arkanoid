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

#include "Physics/Body.h"

#include "Physics.h"

ar::Physics::Physics() {
    cocos2d::Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
}

ar::Physics::~Physics() {
    cocos2d::Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
}

void ar::Physics::update(float delta) {
    updateAgents();
    checkCollisions();
}

void ar::Physics::updateAgents() {
    for (const auto &agent : mAgents) {
        const auto &pos = agent->getPosition();
        const auto &velocity = agent->getVelocity();
        agent->setPosition(pos + velocity);
    }
}

void ar::Physics::checkCollisions() {
    for (const auto &agent : mAgents) {
        for (const auto &obstacle : mObstacles) {
            const auto result = getCollisionResult(agent, obstacle);

            if (!result.equals(cocos2d::Vec2::ZERO)) {
                const auto &velocity = agent->getVelocity();
                agent->setVelocity({velocity.x * result.x, velocity.y * result.y});
            }
        }
    }
}

cocos2d::Vec2 ar::Physics::getCollisionResult(ar::Body *agent, ar::Body *obstacle) const {
    const auto &agentPos = agent->getPosition();
    const auto &obstaclePos = obstacle->getPosition();
    const auto &obstacleSize = obstacle->getContentSize();

    cocos2d::Vec2 nearest = agentPos;
    cocos2d::Vec2 result{1.F, 1.F};

    // Horizontal

    if (agentPos.x < obstaclePos.x) {
        nearest.x = obstaclePos.x;
        result.x = -1.F;
    } else if (agentPos.x > obstaclePos.x + obstacleSize.width) {
        nearest.x = obstaclePos.x + obstacleSize.width;
        result.x = -1.F;
    }

    // Vertical

    if (agentPos.y < obstaclePos.y) {
        nearest.y = obstaclePos.y;
        result.y = -1.F;
    } else if (agentPos.y > obstaclePos.y + obstacleSize.height) {
        nearest.y = obstaclePos.y + obstacleSize.height;
        result.y = -1.F;
    }

    // Distance

    const cocos2d::Vec2 diff = agentPos - nearest;
    const float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

    if (distance <= agent->getContentSize().width / 2) {
        return result;
    } else {
        return {};
    }
}

void ar::Physics::registerAgent(ar::Body *agent) {
    mAgents.push_back(agent);
}

void ar::Physics::registerObstacle(ar::Body *obstacle) {
    mObstacles.push_back(obstacle);
}

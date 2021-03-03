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

ar::Physics::Physics(size_t ticksPerFrame) : mTicksPerFrame(ticksPerFrame) {
    cocos2d::Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
}

ar::Physics::~Physics() {
    cocos2d::Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
}

void ar::Physics::update(float delta) {
    for (size_t i = 0; i < mTicksPerFrame; ++i) {
        updateAgents();
        checkCollisions();
    }
}

void ar::Physics::updateAgents() {
    for (const auto &agent : mAgents) {
        agent->updatePosition();
    }
}

void ar::Physics::checkCollisions() {
    for (const auto &agent : mAgents) {
        for (const auto &obstacle : mObstacles) {
            if (agent == obstacle || !obstacle->isVisible()) {
                continue;
            }

            if (agent->isCollided(obstacle)) {
                agent->updateVelocityAfterCollision(obstacle);
            }
        }
    }
}

void ar::Physics::registerAgent(ar::Body *agent) {
    mAgents.push_back(agent);
}

void ar::Physics::registerObstacle(ar::Body *obstacle) {
    mObstacles.push_back(obstacle);
}

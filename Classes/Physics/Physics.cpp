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
        const auto speed = agent->getSpeed();

        agent->setPosition(pos + velocity * speed);
    }
}

void ar::Physics::checkCollisions() {
    for (const auto &agent : mAgents) {
        for (const auto &obstacle : mObstacles) {
            if (agent == obstacle) {
                continue;
            }

            auto result = agent->getCollisionVelocity(obstacle);

            if (!result.equals({})) {
                const auto &velocity = agent->getVelocity();
                const auto &ob_velocity = obstacle->getVelocity();
                const auto ob_friction = obstacle->getFriction();

                const cocos2d::Vec2 new_velocity{
                        velocity.x + result.x + ob_velocity.x * ob_friction,
                        velocity.y + result.y + ob_velocity.y * ob_friction};

                agent->setVelocity(new_velocity.getNormalized());
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

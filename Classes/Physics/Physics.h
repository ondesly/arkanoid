//
//  Physics.h
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <vector>

namespace ar {

    class Agent;

    class Body;

    class Physics {
    public:

        Physics();

        ~Physics();

    public:

        void update(float delta);

        void registerAgent(Agent *agent);

        void registerObstacles(Body *obstacle);

    private:

        std::vector<Agent *> mAgents;
        std::vector<Body *> mObstacles;

    private:

        void updateAgents();

        void checkCollisions();

        cocos2d::Vec2 getCollisionResult(Agent *agent, Body *obstacle) const;

    };

}
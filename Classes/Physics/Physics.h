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

    class Body;

    class Physics {
    public:

        Physics(size_t ticksPerFrame);

        ~Physics();

    public:

        void update(float delta);

        void registerAgent(Body *agent);

        void registerObstacle(Body *obstacle);

    private:

        const size_t mTicksPerFrame;

        std::vector<Body *> mAgents;
        std::vector<Body *> mObstacles;

    private:

        void updateAgents();

        void checkCollisions();

    };

}
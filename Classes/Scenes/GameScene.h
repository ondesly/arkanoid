//
//  GameScene.h
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <2d/CCScene.h>

namespace ar {

    class GameScene : public cocos2d::Scene {
    public:

        static GameScene *create();

    public:

        bool init() override;

    };

}
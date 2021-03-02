//
//  GameScene.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 02.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include "GameScene.h"

ar::GameScene *ar::GameScene::create() {
    auto scene = new(std::nothrow) GameScene();
    if (scene && scene->init()) {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

bool ar::GameScene::init() {
    if (!cocos2d::Scene::init()) {
        return false;
    }

    return true;
}
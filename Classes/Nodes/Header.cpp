//
//  Header.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 04.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <string>

#include <2d/CCLabel.h>
#include <2d/CCSprite.h>
#include <base/CCEventDispatcher.h>
#include <base/CCEventListenerCustom.h>

#include "Resources.h"

#include "Header.h"

namespace {

    const char *cScoreTitle = "SCORE";

}

ar::Header *ar::Header::create(const cocos2d::Size &size) {
    auto header = new(std::nothrow) Header();
    if (header && header->init(size)) {
        header->autorelease();
        return header;
    }
    CC_SAFE_DELETE(header);
    return nullptr;
}

bool ar::Header::init(const cocos2d::Size &size) {
    if (!cocos2d::Node::init()) {
        return false;
    }

    setContentSize(size);

    //

    auto bg = cocos2d::Sprite::createWithSpriteFrameName(texture::game::empty);
    bg->setColor(cocos2d::Color3B::BLACK);
    bg->setScale(getContentSize().width / bg->getContentSize().width, getContentSize().height / bg->getContentSize().height);
    bg->setPosition(getContentSize() / 2);
    addChild(bg);

    //

    const float fontSize = getContentSize().height * 0.7F;

    auto scoreTitle = cocos2d::Label::createWithTTF(cScoreTitle, font::arcadeClassic, fontSize, {},
            cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
    scoreTitle->setTextColor(cocos2d::Color4B::RED);
    scoreTitle->setPosition({getContentSize().width / 2, getContentSize().height / 4 * 3});
    addChild(scoreTitle);

    mScoreValue = cocos2d::Label::createWithTTF(std::to_string(mScore), font::arcadeClassic, fontSize, {},
            cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
    mScoreValue->setPosition({getContentSize().width / 2, getContentSize().height / 4});
    addChild(mScoreValue);

    //

    auto onBlockDestroyed = cocos2d::EventListenerCustom::create(event::onBlockDestroyed, [&](cocos2d::EventCustom *event) {
        mScore += score::blockValue;
        mScoreValue->setString(std::to_string(mScore));
    });
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(onBlockDestroyed, this);

    //

    return true;
}
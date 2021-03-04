//
//  Dialog.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 04.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <ui/UIButton.h>

#include "Resources.h"

#include "Dialog.h"

namespace {

    const char *cButtonTitle = "REPLAY";

    const float cTitleSize = 1.F;
    const float cScoreSize = 1.5F;
    const float cButtonSize = 0.6F;

}

ar::Dialog *ar::Dialog::create(const cocos2d::Size &size, const std::string &title, const std::string &score,
        const std::function<void(Dialog *)> &onClose) {
    auto dialog = new(std::nothrow) Dialog();
    if (dialog && dialog->init(size, title, score, onClose)) {
        dialog->autorelease();
        return dialog;
    }
    CC_SAFE_DELETE(dialog);
    return nullptr;
}

bool ar::Dialog::init(const cocos2d::Size &size, const std::string &title, const std::string &score,
        const std::function<void(Dialog *)> &onClose) {
    if (!cocos2d::Node::init()) {
        return false;
    }

    setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
    setContentSize(size);

    // Back

    auto back = cocos2d::Sprite::create();
    back->setOpacity(opacity::dialogBack);
    back->setColor(cocos2d::Color3B::BLACK);
    back->setAnchorPoint(cocos2d::Vec2::ZERO);
    back->setTextureRect({{}, getContentSize()});
    addChild(back);

    // Labels

    const float baseFontSize = getContentSize().width * 0.1F;

    auto dialogTitle = cocos2d::Label::createWithTTF(title, font::arcadeClassic, baseFontSize * cTitleSize, {},
            cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
    dialogTitle->setPosition({getContentSize().width / 2, getContentSize().height / 6 * 5 - dialogTitle->getContentSize().height});
    addChild(dialogTitle);

    auto scoreValue = cocos2d::Label::createWithTTF(score, font::arcadeClassic, baseFontSize * cScoreSize, {},
            cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
    scoreValue->setTextColor(cocos2d::Color4B::RED);
    scoreValue->setPosition({getContentSize().width / 2, getContentSize().height / 6 * 5 - dialogTitle->getContentSize().height - scoreValue->getContentSize().height});
    addChild(scoreValue);

    // Button

    auto button = makeButton(cButtonTitle, baseFontSize * cButtonSize);
    button->setPosition(getContentSize() / 2);

    button->addTouchEventListener([&, onClose](Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            onClose(this);
        }
    });

    addChild(button);

    //

    return true;
}

cocos2d::ui::Button *ar::Dialog::makeButton(const std::string &title, float fontSize) const {
    auto button = cocos2d::ui::Button::create(texture::game::button, texture::game::buttonDown, "",
            cocos2d::ui::Widget::TextureResType::PLIST);
    button->setScale9Enabled(true);

    const auto texSize = button->getNormalTextureSize();
    button->setCapInsets({texSize.width * 0.25F, texSize.height * 0.25F, texSize.width * 0.25F, texSize.height * 0.25F});

    button->setTitleFontName(font::arcadeClassic);
    button->setTitleText(title);
    button->setTitleColor(cocos2d::Color3B::BLACK);
    button->setTitleFontSize(fontSize);

    button->setUnifySizeEnabled(true);
    button->setContentSize(button->getVirtualRendererSize() * 1.4F);

    return button;
}

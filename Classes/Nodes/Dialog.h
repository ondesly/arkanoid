//
//  Dialog.h
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 04.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <functional>
#include <string>

#include <2d/CCNode.h>

namespace cocos2d {

    namespace ui {

        class Button;

    }

}

namespace ar {

    class Dialog : public cocos2d::Node {
    public:

        static Dialog *create(const cocos2d::Size &size, const std::string &title, const std::string &score,
                const std::function<void()> &onClose);

    public:

        bool init(const cocos2d::Size &size, const std::string &title, const std::string &score,
                const std::function<void()> &onClose);

    private:

        cocos2d::ui::Button *makeButton(const std::string &title, float fontSize) const;

    };

}
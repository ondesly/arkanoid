//
//  Resources.h
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 04.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

namespace ar {

    namespace texture {

        namespace bg {

            extern const char *bg;

        }

        namespace game {

            extern const char *empty;

            extern const char *ball;
            extern const char *platform;
            extern const char *platformShadow;
            extern const char *block;

            extern const char *tube;
            extern const char *tubeDecor;
            extern const char *tubeCornerLeft;
            extern const char *tubeCornerRight;

            extern const char *button;
            extern const char *buttonDown;

        }

    }

    namespace font {

        extern const char *arcadeClassic;

    }

    namespace event {

        extern const char *onBlockDestroyed;

    }

    namespace score {

        extern const size_t blockValue;

    }

    namespace opacity {

        extern const uint8_t shadow;
        extern const uint8_t dialogBack;

    }

}
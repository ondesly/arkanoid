//
//  Resources.cpp
//  Arkanoid
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 04.03.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include "Resources.h"

namespace ar {

    namespace texture {

        namespace bg {

            const char *bg = "bg";

        }

        namespace game {

            const char *empty = "empty";

            const char *ball = "ball";
            const char *platform = "platform";
            const char *platformShadow = "platform_shadow";
            const char *block = "block";

            const char *tube = "tube";
            const char *tubeDecor = "tube_decor";
            const char *tubeCornerLeft = "tube_corner_left";
            const char *tubeCornerRight = "tube_corner_right";

        }

    }

    namespace font {

        const char *arcadeClassic = "arcadeclassic.ttf";

    }

    namespace event {

        const char *onBlockDestroyed = "onBlockDestroyed";

    }

    namespace score {

        const size_t blockValue = 10;

    }

    const uint8_t cShadowOpacity = 100;

}
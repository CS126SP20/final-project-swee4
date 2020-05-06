// Copyright (c) 2020 [Sue Wee]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_BOSS_H_
#define FINALPROJECT_MYLIBRARY_BOSS_H_

#include <vector>
#include <mylibrary/tile.h>
#include "mylibrary/ciAnimatedGif.h"

namespace mylibrary {
    using std::vector;
    class FinalBoss {
    public:
        FinalBoss(vector<Tile> boss_tiles);
    private:
        vector<Tile> tiles_occupied;
        cinder::ciAnimatedGifRef current_image;

    };

}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_BOSS_H_

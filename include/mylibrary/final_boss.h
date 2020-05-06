// Copyright (c) 2020 [Sue Wee]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_BOSS_H_
#define FINALPROJECT_MYLIBRARY_BOSS_H_

#include <vector>
#include <mylibrary/tile.h>
#include "mylibrary/ciAnimatedGif.h"
#include <string>

namespace mylibrary {
    using std::vector;
    using std::string;

    class FinalBoss {
    public:
        FinalBoss();
        FinalBoss(vector<Tile> boss_tiles);
        string GetDescription();
        string GetInteractionInstructions();
        cinder::ciAnimatedGifRef GetImage();
        size_t GetMinXTile();
        size_t GetMaxXTile();
        size_t GetMinYTile();
        size_t GetMaxYTile();
        void TakeDamage(size_t value);
        size_t GetDamage();
        void AttackMode();
        void DefaultMode();
        size_t GetCurrentHealth();
        vector<Tile> GetOccupiedTiles();

    private:
        vector<Tile> occupied_tiles;
        cinder::ciAnimatedGifRef image;
        size_t current_health;
        size_t total_health;
        string description;
        string interaction_instructions;
        size_t min_x_tile;
        size_t max_x_tile;
        size_t min_y_tile;
        size_t max_y_tile;
        size_t damage;
    };

}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_BOSS_H_

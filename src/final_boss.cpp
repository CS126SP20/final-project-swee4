// Copyright (c) 2020 [Sue Wee]. All rights reserved.

#include <mylibrary/final_boss.h>

namespace mylibrary {

FinalBoss::FinalBoss() :
    occupied_tiles {},
    image (cinder::ciAnimatedGif::create(ci::app::loadAsset("turret default.gif"))),
    total_health(0),
    description(""),
    interaction_instructions(""),
    min_x_tile(0),
    min_y_tile(0),
    max_x_tile(0),
    max_y_tile(0),
    damage(0)
    { current_health = total_health;}

FinalBoss::FinalBoss(const vector<Tile>& boss_tiles) {
    occupied_tiles = boss_tiles;
    image = cinder::ciAnimatedGif::create(ci::app::loadAsset("turret default.gif"));
    total_health = 300;
    current_health = total_health;
    damage = 25;
    UpdateDescription();
    interaction_instructions = "\nAttack with [SPACE] or [Q].";
    SetMinMaxTiles();
}

void FinalBoss::UpdateDescription() {
    description = "You've reached the NEXUS TURRET! You'll need to attack it with your BEES! But be careful, "
                  "the turret will retaliate each time it is attacked!"
                  "\nHP: " + std::to_string(current_health) + "/" + std::to_string(total_health);
}

void FinalBoss::SetMinMaxTiles() {
    Tile& first_tile = occupied_tiles[0];
    min_x_tile = first_tile.GetXTile();
    min_y_tile = first_tile.GetYTile();
    max_x_tile = first_tile.GetXTile();
    max_y_tile = first_tile.GetYTile();
    for (Tile current : occupied_tiles) {
        size_t current_x = current.GetXTile();
        size_t current_y = current.GetYTile();
        if (current_x < min_x_tile) {
            min_x_tile = current_x;
        } else if (current_x > max_x_tile) {
            max_x_tile = current_x;
        }
        if (current_y < min_y_tile) {
            min_y_tile = current_y;
        } else if (current_y > max_y_tile) {
            max_y_tile = current_y;
        }
    }
}

string FinalBoss::GetDescription() {
    return description;
}

string FinalBoss::GetInteractionInstructions() {
    return interaction_instructions;
}

cinder::ciAnimatedGifRef& FinalBoss::GetImage() {
    return image;
}

size_t FinalBoss::GetMinXTile() {
    return min_x_tile;
}

size_t FinalBoss::GetMaxXTile() {
    return max_x_tile;
}

size_t FinalBoss::GetMinYTile() {
    return min_y_tile;
}

size_t FinalBoss::GetMaxYTile() {
    return max_y_tile;
}

void FinalBoss::TakeDamage(size_t value) {
    if (value > current_health) {
        current_health = 0;
    } else {
        current_health -= value;
    }
    UpdateDescription();
}

size_t FinalBoss::GetDamage() {
    return damage;
}

void FinalBoss::AttackMode() {
    image = cinder::ciAnimatedGif::create( ci::app::loadAsset("turret attack.gif"));
}

void FinalBoss::DefaultMode() {
    image = cinder::ciAnimatedGif::create(ci::app::loadAsset("turret default.gif"));
}

size_t FinalBoss::GetCurrentHealth(){
    return current_health;
}

vector<Tile> FinalBoss::GetOccupiedTiles() {
    return occupied_tiles;
}

}  // namespace mylibrary

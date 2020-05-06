// Copyright (c) 2020 [Sue Wee]. All rights reserved.

#include <mylibrary/character.h>

namespace mylibrary {

Character::Character() {
    current_x_tile = 1;
    current_y_tile = 1;
    tile_length = 64;
    current_image = cinder::ciAnimatedGif::create( ci::app::loadAsset("beemo right.gif"));
    orientation = "right";
    ap = 20;
    total_hp = 100;
    current_hp = total_hp;
    ammo = 0;
}

Character::Character(size_t start_x_tile, size_t start_y_tile, size_t tile_size, string image_file_name) {
    current_x_tile = start_x_tile;
    current_y_tile = start_y_tile;
    tile_length = tile_size;
    current_image = cinder::ciAnimatedGif::create( ci::app::loadAsset(image_file_name));
    orientation = "right";
    ap = 20;
    total_hp = 100;
    current_hp = total_hp;
    ammo = 0;
}

size_t Character::GetXTile() {
    return current_x_tile;
}

size_t Character::GetYTile() {
    return current_y_tile;
}

void Character::SetXTile(size_t tile_index) {
    current_x_tile = tile_index;
}

void Character::SetYTile(size_t tile_index) {
    current_y_tile = tile_index;
}

size_t Character::GetXStartPixel(){
    return (current_x_tile - 1) * tile_length;
}

size_t Character::GetYStartPixel(){
    return (current_y_tile - 1) * tile_length;
}

size_t Character::GetXEndPixel() {
    return current_x_tile * tile_length;
}

size_t Character::GetYEndPixel() {
    return current_y_tile * tile_length;
}

cinder::ciAnimatedGifRef Character::GetImage() {
    return current_image;
}

void Character::SetImage(string new_orientation) {
    orientation = new_orientation;
    current_image = cinder::ciAnimatedGif::create( ci::app::loadAsset("beemo "+ orientation + ".gif"));
}

string Character::GetOrientation() {
    return orientation;
}

size_t Character::GetTotalAP() {
    return ap;
}
size_t Character::GetTotalHP() {
    return total_hp;
}

size_t Character:: GetCurrentHP() {
    return current_hp;
}

size_t Character:: GetCurrentAmmoCount() {
    return ammo;
}

void Character::AttackMode() {
    current_image = cinder::ciAnimatedGif::create( ci::app::loadAsset("beemo attack "+ orientation +".gif"));
}

void Character::Grab(mylibrary::Item item_to_grab) {
    current_image = cinder::ciAnimatedGif::create( ci::app::loadAsset("beemo grab "+ orientation +".gif"));
    string acronym = item_to_grab.GetBuffAcronym();
    size_t value = item_to_grab.GetValue();
    if (item_to_grab.GetBuffAcronym() != "BE") {
        inventory.push_back(item_to_grab);
    }
    if (acronym == "BE") {
        ammo += value;
    } else if (acronym == "AP") {
        ap += value;
    } else if (acronym == "HP") {
        total_hp += value;
        current_hp += value;
    }
}

void Character::UseAmmo() {
    ammo--;
}

vector<Item> Character::GetInventory() {
    return inventory;
}

bool Character::IsInventoryFull() {
    return inventory.size() == 6;
}

void Character::TakeDamage(size_t damage_value) {
    if (damage_value > current_hp) {
        current_hp = 0;
    } else {
        current_hp -= damage_value;
    }
}

}  // namespace mylibrary

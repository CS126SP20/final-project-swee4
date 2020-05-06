// Copyright (c) 2020 [Sue Wee]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_CHARACTER_H_
#define FINALPROJECT_MYLIBRARY_CHARACTER_H_

#include "mylibrary/ciAnimatedGif.h"
#include <mylibrary/item.h>
#include <string>
#include <vector>

namespace mylibrary {
using std::string;
using std::vector;
class Character {
public:
    Character();
    Character(size_t start_x_tile, size_t start_y_tile, size_t tile_size, string image_file_name);
    size_t GetXTile();
    size_t GetYTile();
    void SetXTile(size_t tile_index);
    void SetYTile(size_t tile_index);
    size_t GetXStartPixel();
    size_t GetYStartPixel();
    size_t GetXEndPixel();
    size_t GetYEndPixel();
    cinder::ciAnimatedGifRef GetImage();
    void SetImage(string orientation);
    string GetOrientation();
    void AttackMode();
    void Grab(mylibrary::Item item_to_grab);
    void UseAmmo();
    vector<Item> GetInventory();
    bool IsInventoryFull();
    size_t GetTotalAP();
    size_t GetTotalHP();
    size_t GetCurrentHP();
    size_t GetCurrentAmmoCount();
    private:
    size_t current_x_tile;
    size_t current_y_tile;
    size_t tile_length;
    cinder::ciAnimatedGifRef current_image;
    string orientation;
    size_t ap;
    size_t current_hp;
    size_t total_hp;
    size_t ammo;
    vector<Item> inventory;
};
}  // namespace mylibrary

#endif // FINALPROJECT_CHARACTER_EXAMPLE_H_

// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include "cinder/app/RendererGl.h"
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <mylibrary/character.h>
#include <mylibrary/playing_field.h>

namespace myapp {

class MyApp : public cinder::app::App {
public:
    MyApp();
    void setup() override;
    void update() override;
    void draw() override;
    void keyDown(cinder::app::KeyEvent) override;
private:
    mylibrary::PlayingField current_scene;
    mylibrary::PlayingField scene_one;
    mylibrary::PlayingField scene_two;
    mylibrary::Character beemo;
    bool CanMove(const std::string& direction);
    bool IsWithinSceneBounds(const std::string& direction);
    mylibrary::Tile GetFrontTile();
    size_t GetFrontTileX();
    size_t GetFrontTileY();
    void DrawDescription();
    void DrawInventory();
    void DrawStats();
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_

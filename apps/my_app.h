// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <mylibrary/playing_field.h>
#include "cinder/app/RendererGl.h"


namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
private:

    cinder::gl::Texture2dRef mBackground_;
    mylibrary::PlayingField scene_one;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_

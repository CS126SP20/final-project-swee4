// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "../src/ciAnimatedGif.h"

#include <cinder/app/App.h>


namespace myapp {

using cinder::app::KeyEvent;

    cinder::ciAnimatedGifRef mGif;

MyApp::MyApp() { }

void MyApp::setup() {
    mBackground_ = cinder::gl::Texture2d::create(loadImage(loadAsset("transparent-tree.png")));
    mGif = cinder::ciAnimatedGif::create( loadAsset("cherry-blossom.gif"));
}

void MyApp::update() { }

void MyApp::draw() {
    cinder::gl::clear();
    // drawing background image to fit frame:
    // https://libcinder.org/docs/guides/tour/hello_cinder_chapter1.html
    cinder::gl::draw( mBackground_ ,getWindowBounds());
    mGif->draw();
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp

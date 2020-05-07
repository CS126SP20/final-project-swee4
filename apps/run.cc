// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>

#include "beemos_rescue.h"


using cinder::app::App;
using cinder::app::RendererGl;


namespace myapp {

const int kSamples = 8;
const int kWidth = 64 * 12;
const int kHeight = 64 * 12;

void SetUp(App::Settings* settings) {
  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("Beemo's Rescue");
}

}  // namespace myapp


// This is a macro that runs the application.
CINDER_APP(myapp::GameEngine,
           RendererGl(RendererGl::Options().msaa(myapp::kSamples)),
           myapp::SetUp)

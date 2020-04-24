// Library from: https://github.com/cwhitney/ciAnimatedGif

#pragma once

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

namespace cinder {

    using ciAnimatedGifRef = std::shared_ptr<class ciAnimatedGif>;

    class ciAnimatedGif {
    public:
        ciAnimatedGif() = default; //was delete before
        ciAnimatedGif(ci::DataSourceRef data);

        static ciAnimatedGifRef create(ci::DataSourceRef data){ return std::make_shared<ciAnimatedGif>(data); }
        static ciAnimatedGifRef create( const cinder::fs::path &path){ return ciAnimatedGif::create( (cinder::DataSourceRef)cinder::DataSourcePath::create( path )); }

        void update();
        void draw();
        //method added for this specific project:
        void draw(size_t min_x_coord, size_t min_y_coord, size_t max_x_coord, size_t max_y_coord);
        void play();
        void seek( float pct );

        const std::vector<ci::Color> getPalette(){ return mColorList; };

        ci::gl::TextureRef              getTexture(){ return mCurTex; }

    protected:

        void parseMetadata(ci::DataSourceRef data);
        void printBit(uint8_t byte);

        std::vector<ci::gl::TextureRef> mFrameList;
        std::vector<float>              mFrameTimes;

        double                          mNextFrameTime = -1;
        int                             mCurFrame = -1;
        ci::gl::TextureRef              mCurTex = nullptr;

        std::string                     mHeader;

        uint16_t                        canvasWidth, canvasHeight;
        bool                            hasGlobalColorTable = false;
        std::vector<ci::Color>          mColorList;
    };

}
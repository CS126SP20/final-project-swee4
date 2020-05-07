// External library from: https://github.com/cwhitney/ciAnimatedGif
// Note: Edited the default constructor and added an overloaded draw method in order to make this work with my own
// project purposes. Only the edited methods will have Javadoc comments added because they are the only ones that I
// have edited.

#pragma once

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

namespace cinder {

    using ciAnimatedGifRef = std::shared_ptr<class ciAnimatedGif>;

    class ciAnimatedGif {
    public:

        /** Default constructor was delete() at first, but that caused the program to crash and had to be edited. **/
        ciAnimatedGif() = default;

        ciAnimatedGif(ci::DataSourceRef data);

        static ciAnimatedGifRef create(ci::DataSourceRef data){ return std::make_shared<ciAnimatedGif>(data); }

        static ciAnimatedGifRef create( const cinder::fs::path &path){ return ciAnimatedGif::create( (cinder::DataSourceRef)cinder::DataSourcePath::create( path )); }

        void update();

        void draw();

        //method added for this specific project:
        /**
         * Draws the animated gif but every frame is resized to fit between the rectangular bounds of the minimum x
         * and y coordinates and the maximum x and y coordinates, all in pixel.
         * @param min_x_coord Value of the leftmost pixel coordinate.
         * @param min_y_coord Value of the bottommost pixel coordinate.
         * @param max_x_coord Value of the rightmost pixel coordinate.
         * @param max_y_coord Value of the topmost pixel coordinate.
         */
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
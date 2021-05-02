//
// Created by huguntu on 24/04/21.
//

#ifndef ANT_ENGINE_RENDERER_H
#define ANT_ENGINE_RENDERER_H

#include "../util.h"

namespace antEngine {
    class Camera;
    class Renderer {
    public:
        Camera* currentCamera= nullptr;
        /*
            Renders a square
        */
        virtual void renderSquare(int x, int y, int size, RGBA color, bool stroke=false, int stroke_size=1) = 0;


        virtual void renderLine(int x1, int y1, int x2, int y2, RGBA color) = 0;

        /*
            Checks if any relevant event has happened
        */
        virtual void checkEvents() = 0;

        virtual void registerMouseHandler(MouseHandler& handler) = 0;

        virtual void drawWorldPixel(int x, int y, RGBA color)=0;

        /*
            Used to set the color of a pixel in the current frame
        */
        virtual void drawPixel(unsigned int x, unsigned int y, RGBA color) = 0;

        // renders the current frame
        virtual void renderFrame() = 0;

        //clears the pixels of the current frame;
        virtual void clearFrame() = 0;

        // returns true if the window is still open, false otherwise
        virtual bool windowOpen() = 0;

        inline void setCamera(Camera* camera) {
            this->currentCamera = camera;
        }

        inline Camera* getCurrentCamera() {
            return this->currentCamera;
        }
    };

}

#endif //ANT_ENGINE_RENDERER_H

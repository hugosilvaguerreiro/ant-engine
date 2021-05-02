//
// Created by huguntu on 24/04/21.
//

#ifndef ANT_ENGINE_NCURSESRENDERER_H
#define ANT_ENGINE_NCURSESRENDERER_H

#include <cstdio>
#include <vector>
#include <cstring>
#include <chrono>
#include <thread>
#include <math.h>
#include "Renderer.h"

#define C_WIDTH     4           /* Width of each character in pixels */
#define C_HEIGHT    8           /* Height of each character in pixels */
#define WIDTH       800         /* Screen width */
#define HEIGHT      600         /* Screen height */

#include <ncurses.h>

namespace antEngine {

    // inspired on https://github.com/DinoZ1729/Ray
    class NCursesRenderer : public Renderer {
        std::vector<std::vector<char>> frame;

        WINDOW* mainWindow;
        int rows, columns;
        /* time tracking variables */
    public:
        NCursesRenderer(SIZE size);

        void renderSquare(int x, int y, int size, RGBA color, bool stroke, int stroke_size) override;

        void renderLine(int x1, int y1, int x2, int y2, RGBA color) override;

        void checkEvents() override;

        void registerMouseHandler(MouseHandler &handler) override;

        void drawWorldPixel(int x, int y, RGBA color) override;

        void drawPixel(unsigned int x, unsigned int y, RGBA color) override;

        void renderFrame() override;

        void clearFrame() override;

        bool windowOpen() override;

        void renderLineWithAntiAliasing(int x0, int y0, int x1, int y1, RGBA color);

    };

}


#endif //ANT_ENGINE_NCURSESRENDERER_H

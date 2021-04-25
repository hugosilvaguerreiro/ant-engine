//
// Created by huguntu on 24/04/21.
//

#include "AsciiRenderer.h"
#include <iostream>

const char palette[] = " .:;~=#OB8%&";
// http://paulbourke.net/dataformats/asciiart/
const int palletSize = 12;

using namespace std;

constexpr chrono::nanoseconds timestep(chrono::microseconds(17));  /* Minimum Duration of each loop*/

/* set cursor at start to avoid flickering (avoid clearing screen) */
void gotoxy(short x, short y) {
#ifdef _WIN32
    COORD coord = { x, y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    printf("%c[%d;%df", 0x1B, y, x);
#endif
}

antEngine::AsciiRenderer::AsciiRenderer() : frame(), lag(chrono::nanoseconds(0)) {
    time_start = chrono::high_resolution_clock::now();

    for (int i = 0; i < HEIGHT / C_HEIGHT; i++) {
        this->frame.emplace_back(std::vector<char>());
        for (int j = 0; j < WIDTH / C_WIDTH; j++) {
            this->frame.at(i).push_back(' ');
        }
    }
}

void antEngine::AsciiRenderer::renderSquare(int x, int y, int size, RGBA color, bool stroke, int stroke_size) {
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            unsigned int x1= i+x;
            unsigned int y1= j+y;

            if(x1 < 0) { x1 = 0; } if(x1 > HEIGHT) { x1 = HEIGHT; }
            if(y1 < 0) { y1 = 0; } if(y1 > WIDTH)  { y1 = WIDTH; }

            if(i == 0 || i == size-1 || j == 0 || j == size -1 ) {
                this->drawPixel(x1, y1, color);
            }
        }
    }
}

void antEngine::AsciiRenderer::renderLine(int x1, int y1, int x2, int y2, RGBA color) {

    int dx = x2 - x1;
    int dy = y2 - y1;


    for (int x=x1; x < x2; x++) {
        int y = y1 + dy * (x - x1) / dx;
        this->drawPixel(x, y, color);
    }
}

void antEngine::AsciiRenderer::checkEvents() {

}

void antEngine::AsciiRenderer::registerMouseHandler(MouseHandler &handler) {

}

void antEngine::AsciiRenderer::drawPixel(unsigned int x, unsigned int y, RGBA color) {

    this->frame[x/C_HEIGHT][y/C_WIDTH] = palette[color.A/22];
}

void antEngine::AsciiRenderer::renderFrame() {
    time_start = chrono::high_resolution_clock::now();
    char platno[HEIGHT / C_HEIGHT * (WIDTH / C_WIDTH + 1) + 1];
    int p = 0;
    for (int i = 0; i < HEIGHT / C_HEIGHT; i++) {
        for (int j = 0; j < WIDTH / C_WIDTH; j++) {
            platno[p++] = this->frame[i][j];
        }
        platno[p++] = '\n';
    }
    platno[p] = 0;
    puts(platno);
    gotoxy(0,0);

    /* elapsed time of this loop */
    time_end = std::chrono::high_resolution_clock::now();
    lag = std::chrono::duration_cast<std::chrono::nanoseconds>(time_start - time_end);

    /* sleeping for the remaning duration to get a constant refreh rate */
    if (lag < timestep) {
        auto sleep_duration = (timestep - lag);
        sleep_duration = chrono::milliseconds(10);
        this_thread::sleep_for(sleep_duration);
    }
}

void antEngine::AsciiRenderer::clearFrame() {

}

bool antEngine::AsciiRenderer::windowOpen() {
    return true;
}


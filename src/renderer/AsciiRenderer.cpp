//
// Created by huguntu on 24/04/21.
//

#include "AsciiRenderer.h"
#include <iostream>

const char palette[] = " .:;~=#OB8%&";
//const char palette[] = " .\'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
;
// http://paulbourke.net/dataformats/asciiart/
//const int palletSize = 70;

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
    this->renderLineWithAntiAliasing(x1, y1, x2, y2, color);

    /*int dx = x2 - x1;
    int dy = y2 - y1;

    for (int x=x1; x < x2; x++) {
        int y = y1 + dy * (x - x1) / dx;
        this->drawPixel(x, y, color);
    }*/
}

void antEngine::AsciiRenderer::checkEvents() {

}

void antEngine::AsciiRenderer::registerMouseHandler(MouseHandler &handler) {

}

void antEngine::AsciiRenderer::drawPixel(unsigned int x, unsigned int y, RGBA color) {
    // 3.64 = 255/palettesize
    this->frame[x/C_HEIGHT][y/C_WIDTH] = palette[(int)((float)color.A/21.25f)];
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


float ipart(float x) {
    return floor(x);
}

float iround(float x) {
    return ipart(x + 0.5f);
}

float fpart(float x) {
    return x - floor(x);
}

float rfpart(float x) {
    return 1.0f - fpart(x);
}


void antEngine::AsciiRenderer::renderLineWithAntiAliasing(int x0, int y0, int x1, int y1, RGBA color) {
    //https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm

    bool steep = abs(y1 - y0) > abs(x1 - x0);

    if(steep) {
        swap(x0, y0);
        swap(x1, y1);
    }

    if(x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    float gradient = (float)dy / (float)dx;
    if(dx == 0.0) {
        gradient = 1.0;
    }

    //handle first endpoint
    float xend = round(x0);
    float yend = (float)y0 + gradient * (xend - (float)x0);
    float xgap = rfpart((float) (x0 + 0.5));
    float xpxl1 = xend; // this will be used in the main loop
    float ypxl1 = ipart(yend);
    if(steep) {
        RGBA c1 = RGBA{0,0,0, (unsigned short)((float)color.A * rfpart(yend) * xgap)};
        RGBA c2 = RGBA{0,0,0, (unsigned short)((float)color.A * fpart(yend) * xgap)};

        this->drawPixel(ypxl1,   xpxl1, c1); // rfpart(yend) * xgap);
        this->drawPixel(ypxl1+1, xpxl1, c2); // fpart(yend) * xgap);
    } else {
        RGBA c1 = RGBA{0,0,0, (unsigned short)((float)color.A * rfpart(yend) * xgap)};
        RGBA c2 = RGBA{0,0,0, (unsigned short)((float)color.A * fpart(yend) * xgap)};

        this->drawPixel(xpxl1, ypxl1  , c1); //rfpart(yend) * xgap)
        this->drawPixel(xpxl1, ypxl1+1, c2); // fpart(yend) * xgap)
    }
    float intery = yend + gradient; // first y-intersection for the main loop


    // handle second endpoint
    xend = round(x1);
    yend = y1 + gradient * (xend - x1);
    xgap = fpart(x1 + 0.5);
    float xpxl2 = xend; //this will be used in the main loop
    float ypxl2 = ipart(yend);
    if(steep) {
        RGBA c1 = RGBA{0,0,0, (unsigned short)((float)color.A * rfpart(yend) * xgap)};
        RGBA c2 = RGBA{0,0,0, (unsigned short)((float)color.A * fpart(yend) * xgap)};

        this->drawPixel(ypxl2  , xpxl2, c1); //rfpart(yend) * xgap);
        this->drawPixel(ypxl2+1, xpxl2, c2); //fpart(yend) * xgap);
    } else {
        RGBA c1 = RGBA{0,0,0, (unsigned short)((float)color.A * rfpart(yend) * xgap)};
        RGBA c2 = RGBA{0,0,0, (unsigned short)((float)color.A * fpart(yend) * xgap)};

        this->drawPixel(xpxl2, ypxl2, c1); // rfpart(yend) * xgap);
        this->drawPixel(xpxl2, ypxl2+1, c2); //fpart(yend) * xgap);
    }

    // main loop
    if(steep) {
        for (int x = xpxl1+1; x < xpxl2 - 1; x++) {
            RGBA c = RGBA{0,0,0, (unsigned short)((float)color.A * rfpart(intery))};

            this->drawPixel(ipart(intery)  , x, c);// rfpart(intery))
            this->drawPixel(ipart(intery)+1, x, c);//  fpart(intery))
            intery = intery + gradient;
        }
    } else {
        for(int x = xpxl1 + 1; x < xpxl2 - 1; x++) {
            RGBA c = RGBA{0,0,0, (unsigned short)((float)color.A * rfpart(intery))};

            this->drawPixel(x, ipart(intery), c); //rfpart(intery))
            this->drawPixel(x, ipart(intery)+1, c); // fpart(intery))
            intery = intery + gradient;
        }
    }

}


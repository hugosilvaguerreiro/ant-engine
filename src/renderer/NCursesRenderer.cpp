//
// Created by huguntu on 24/04/21.
//

#include "AsciiRenderer.h"
#include "NCursesRenderer.h"
#include <ncurses.h>

const char palette[] = " .:;~=#OB8%&";
//const char palette[] = " .\'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

using namespace std;

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0);		/* 0, 0 gives default characters
					 * for the vertical and horizontal
					 * lines			*/
    wrefresh(local_win);		/* Show that box 		*/

    return local_win;
}


antEngine::NCursesRenderer::NCursesRenderer() {


    //initscr();			/* Start curses mode 		  */
    //refresh();			/* Print it on to the real screen */
    initscr();			    /* Start curses mode 		*/
    cbreak();			    /* Line buffering disabled, Pass on
					        * everty thing to me 		*/
    curs_set(0);
    refresh();
    this->mainWindow = create_newwin(500, 500, 0, 0);

    getmaxyx(this->mainWindow, this->rows, this->columns);		/* get the number of rows and columns */

    refresh();

    // initialize frame
    for (int i = 0; i < this->rows; i++) {
        this->frame.emplace_back(std::vector<char>());
        for (int j = 0; j < this->columns; j++) {
            this->frame.at(i).push_back(' ');
        }
    }
    //getch();			/* Wait for user input */
    //endwin();			/* End curses mode		  */
}

void antEngine::NCursesRenderer::renderSquare(int x, int y, int size, RGBA color, bool stroke, int stroke_size) {

}

void antEngine::NCursesRenderer::renderLine(int x1, int y1, int x2, int y2, RGBA color) {
    this->renderLineWithAntiAliasing(x1, y1, x2, y2, color);

    /*if(x2 < x1) {
        swap(x1, x2);
        swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = y2 - y1;

    if(dx == 0) { // vertical line
        if(y1 > y2) {
            swap(y1, y2);
        }

        for (int y=y1; y < y2; y++) {
            this->drawPixel(x1, y, color);
        }
    } else {
        for (int x=x1; x < x2; x++) {
            int y = y1 + dy * (x - x1) / dx;
            this->drawPixel(x, y, color);
        }
    }*/
}

void antEngine::NCursesRenderer::checkEvents() {

}

void antEngine::NCursesRenderer::registerMouseHandler(MouseHandler &handler) {

}

void antEngine::NCursesRenderer::drawPixel(unsigned int x, unsigned int y, RGBA color) {
    this->frame[(int)x*2][(int)y] = palette[(int)((float)color.A/21.25f)];

    refresh();
}


void antEngine::NCursesRenderer::renderFrame() {
    for (int i = 0; i < this->rows; i++) {
        this->frame.emplace_back(std::vector<char>());
        for (int j = 0; j < this->columns; j++) {
            mvprintw(j, i, "%c", this->frame[i][j]);
            // remove the pixel immediately
            this->frame[i][j] = ' ';
        }
    }
    refresh();
}

void antEngine::NCursesRenderer::clearFrame() {
}

bool antEngine::NCursesRenderer::windowOpen() {
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


void antEngine::NCursesRenderer::renderLineWithAntiAliasing(int x0, int y0, int x1, int y1, RGBA color) {
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

        this->drawPixel(ypxl1,   xpxl1, color); // rfpart(yend) * xgap);
        //this->drawPixel(ypxl1+1, xpxl1, color); // fpart(yend) * xgap);
    } else {
        RGBA c1 = RGBA{0,0,0, (unsigned short)((float)color.A * rfpart(yend) * xgap)};
        RGBA c2 = RGBA{0,0,0, (unsigned short)((float)color.A * fpart(yend) * xgap)};

        this->drawPixel(xpxl1, ypxl1  , color); //rfpart(yend) * xgap)
        this->drawPixel(xpxl1, ypxl1+1, color); // fpart(yend) * xgap)
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

        this->drawPixel(ypxl2  , xpxl2, color); //rfpart(yend) * xgap);
        this->drawPixel(ypxl2+1, xpxl2, color); //fpart(yend) * xgap);
    } else {
        RGBA c1 = RGBA{0,0,0, (unsigned short)((float)color.A * rfpart(yend) * xgap)};
        RGBA c2 = RGBA{0,0,0, (unsigned short)((float)color.A * fpart(yend) * xgap)};

        this->drawPixel(xpxl2, ypxl2, color); // rfpart(yend) * xgap);
        this->drawPixel(xpxl2, ypxl2+1, color); //fpart(yend) * xgap);
    }

    // main loop
    if(steep) {
        for (int x = xpxl1+1; x < xpxl2 - 1; x++) {
            RGBA c = RGBA{0,0,0, (unsigned short)((float)color.A * rfpart(intery))};

            this->drawPixel(ipart(intery)  , x, color);// rfpart(intery))
            this->drawPixel(ipart(intery)+1, x, color);//  fpart(intery))
            intery = intery + gradient;
        }
    } else {
        for(int x = xpxl1 + 1; x < xpxl2 - 1; x++) {
            RGBA c = RGBA{0,0,0, (unsigned short)((float)color.A * rfpart(intery))};

            this->drawPixel(x, ipart(intery), color); //rfpart(intery))
            this->drawPixel(x, ipart(intery)+1, color); // fpart(intery))
            intery = intery + gradient;
        }
    }

}


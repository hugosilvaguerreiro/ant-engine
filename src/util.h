//
// Created by huguntu on 24/04/21.
//

#ifndef ANT_ENGINE_UTIL_H
#define ANT_ENGINE_UTIL_H

typedef struct {
    unsigned int width;
    unsigned int height;

} WINDOW_SIZE;

typedef struct {
    unsigned short int R;
    unsigned short int G;
    unsigned short int B;
    unsigned short int A;
} RGBA;


class MouseHandler {
public:
    virtual void onLeftClick(int mousex, int mousey) {}
    virtual void onRightClick(int mousex, int mousey) {}
};

#endif //ANT_ENGINE_UTIL_H
